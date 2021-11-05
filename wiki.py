import os
import sys
import shutil
import tarfile
import dataclasses

from typing import List

import yaml
import requests

from github import Github, GithubException, Repository

from ignored import IGNORED

artifacts = "artifacts"
documentation = "docs"
extract = "docs"
do_not_delete = ["common", "static", "index.md"]

supported = [".md"]


@dataclasses.dataclass
class Meta:
    name: str
    author: str


@dataclasses.dataclass
class Docs:
    contents: List[str]
    repo: Repository
    meta: Meta


if os.path.exists(artifacts):
    shutil.rmtree(artifacts)
os.mkdir(artifacts)

for file in os.listdir(extract):
    if file not in do_not_delete:
        shutil.rmtree(os.path.join(extract, file))

g = Github(os.environ.get("GITHUB_PAT"))
org = g.get_organization("eagletrt")

corpus = []
for repo in org.get_repos():
    if repo.archived:
        print(f"[{repo.full_name}] Skipping. Repository is archived.", file=sys.stderr)
        continue

    if repo.name in IGNORED:
        print(f"[{repo.full_name}] Skipping. Repository is IGNORED!", file=sys.stderr)
        continue

    try:
        repo_contents = repo.get_contents("/")
    except GithubException:
        print(f"[{repo.full_name}] Skipping. Repository is empty.", file=sys.stderr)
        continue

    has_docs = any([content.name == documentation for content in repo_contents])
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

    meta_path = os.path.join(extract_path, "docs.yml")
    if os.path.exists(meta_path) and os.path.isfile(meta_path):
        with open(meta_path) as file:
            raw = yaml.load(file, Loader=yaml.Loader)
        meta = Meta(raw.get("name", repo.name), raw.get("author", "E-Agle TRT"))
    else:
        meta = Meta(repo.name, "E-Agle TRT")

    docs = Docs(contents, repo, meta)
    corpus.append(docs)
