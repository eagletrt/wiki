# Writing Documentation

## Testing the documentation locally

You can test locally the exported documentation using the custom docker image
generated by the wiki project.

1. Open a terminal in the root folder of your project
2. Make sure the `docs/` folder is present
3. Fetch the documentation image:

```bash
docker pull eagletrt/wiki
```

4. Run the autoreloading documentation:

```bash
docker run --rm \
    -p 8000:8000 \
    -v $(pwd)/docs:/wiki/docs/<project-name>:z \
    eagletrt/wiki
```

!!! tip
Live reloading works when testing with docker.

## Ordering pages

You can change the order and titles of your pages by configuring a `.pages`
file anywhere in your documentation file tree.

For more information on the file format take a look at the
[official documentation](https://github.com/lukasgeiter/mkdocs-awesome-pages-plugin).

```yml
title: Example
nav:
    - subdirectory
    - page1.md
    - page2.md
```

## Diagrams

You can draw diagrams with [mermaid](https://mermaid-js.github.io/mermaid/#/).

````
```diagram
stateDiagram-v2
    [*] --> Still
    Still --> [*]

    Still --> Moving
    Moving --> Still
    Moving --> Crash
    Crash --> [*]
```
````

```diagram
stateDiagram-v2
    [*] --> Still
    Still --> [*]

    Still --> Moving
    Moving --> Still
    Moving --> Crash
    Crash --> [*]
```

## Notes and warnings

```
!!! note
    This this a note.
```

!!! note
This this a note.

```
!!! warning
    This this a warning.
```

!!! warning
This this a warning.

Supported types are:

-   `note`
-   `abstract`, `summary`, `tldr`
-   `info`, `todo`
-   `tip`, `hint`, `important`
-   `success`, `check`, `done`
-   `question`, `help`, `faq`
-   `warning`, `caution`, `attention`
-   `failure`, `fail`, `missing`
-   `danger`, `error`
-   `bug`
-   `example`
-   `quote`, `cite`

## Mathematical expressions

```markdown
$x = {-b \pm \sqrt{b^2-4ac} \over 2a}.$
```

$x = {-b \pm \sqrt{b^2-4ac} \over 2a}.$

## Embedding PDFs

```html
<object
    data="../sample.pdf"
    type="application/pdf"
    style="width: 100%; height: 600px"
>
    <embed src="../sample.pdf" type="application/pdf" />
</object>
```

<object data="../sample.pdf" type="application/pdf" style="width: 100%; height: 600px">
    <embed src="../sample.pdf" type="application/pdf" />
</object>