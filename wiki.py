import os
import sys
import shutil
import tarfile
import dataclasses

from typing import List

import requests

from github import Github, GithubException, Repository
from jinja2 import Environment, FileSystemLoader, select_autoescape

documentation = "docs"
artifacts = "artifacts"
extract = "docs"

supported = [".rst", ".md"]

env = Environment(loader=FileSystemLoader("_templates"), autoescape=select_autoescape())

root = env.get_template("root.jinja")


@dataclasses.dataclass
class Docs:
    contents: List[str]
    repo: Repository


for folder in [artifacts, extract]:
    if os.path.exists(folder):
        shutil.rmtree(folder)
    os.mkdir(folder)

g = Github(os.environ.get("GITHUB_PAT"))
org = g.get_organization("eagletrt")

corpus = []
for repo in org.get_repos():
    if repo.archived:
        print(f"[{repo.full_name}] Skipping. Repository is archived.", file=sys.stderr)
        continue

    try:
        contents = repo.get_contents("/")
    except GithubException:
        print(f"[{repo.full_name}] Skipping. Repository is empty.", file=sys.stderr)
        continue

    has_docs = any([content.name == documentation for content in contents])
    if not has_docs:
        print(f"[{repo.full_name}] Skipping. No `docs` folder found.", file=sys.stderr)
        continue

    print(f"[{repo.full_name}] Downloading tarball...")

    url = repo.get_archive_link("tarball")
    download = requests.get(url, stream=True)
    if download.status_code != 200:
        print(f"[{repo.full_name}] Skipping. Tarball download failed.", file=sys.stderr)
        continue

    artifact_path = os.path.join(artifacts, repo.name)
    extract_path = os.path.join(extract, repo.name)

    with open(artifact_path, "wb") as file:
        file.write(download.raw.read())

    print(f"[{repo.full_name}] Extracting `docs` folder...")

    with tarfile.open(artifact_path, "r:gz") as file:
        members = file.getmembers()
        base = os.path.join(members[0].name, documentation) + os.sep
        extractables = [info for info in members if info.name.startswith(base)]
        for extractable in extractables:
            extractable.name = extractable.name[len(base) :]
        file.extractall(extract_path, extractables)

    contents = []
    for item in os.listdir(extract_path):
        path = os.path.join(extract_path, item)
        if os.path.isfile(path):
            doc, ext = os.path.splitext(path)
            if ext in supported:
                contents.append(doc)

    if len(contents) == 0:
        print(f"[{repo.full_name}] Skipping. No root contents.", file=sys.stderr)
        continue

    docs = Docs(contents, repo)
    corpus.append(docs)

if os.path.exists("index.md"):
    os.remove("index.md")

with open("index.md", "w") as file:
    file.write(root.render(corpus=corpus))
