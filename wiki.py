import os
import tarfile
import shutil

import requests

from github import Github, GithubException

artifacts = "_artifacts"
docs = "_docs"

for folder in [artifacts, docs]:
    if os.path.exists(folder):
        shutil.rmtree(folder)
    os.mkdir(folder)

g = Github(os.environ.get("GITHUB_PAT"))
org = g.get_organization("eagletrt")

for repo in org.get_repos():
    if repo.archived:
        continue

    try:
        root = repo.get_contents("/")
    except GithubException:
        # repository is empty
        continue

    has_docs = any([content.name == "docs" for content in root])
    if not has_docs:
        continue

    url = repo.get_archive_link("tarball")
    download = requests.get(url, stream=True)
    if download.status_code != 200:
        continue

    artifact_path = os.path.join(artifacts, repo.name)
    docs_path = os.path.join(docs, repo.name)

    with open(artifact_path, "wb") as file:
        file.write(download.raw.read())

    with tarfile.open(artifact_path, "r:gz") as file:
        members = file.getmembers()
        root = members[0].name
        base = os.path.join(root, "docs") + os.sep
        extractables = [info for info in members if info.name.startswith(base)]
        for extractable in extractables:
            extractable.name = extractable.name[len(base) :]
        file.extractall(docs_path, extractables)
