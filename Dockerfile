FROM python:3.9

ENV PIP_DISABLE_PIP_VERSION_CHECK=on

RUN pip install poetry

WORKDIR /wiki
COPY poetry.lock pyproject.toml ./

RUN poetry config virtualenvs.create false
RUN poetry install --no-interaction

COPY . ./
ENTRYPOINT [ "poetry", "run", "mkdocs", "serve", "-a", "0.0.0.0:8000"]