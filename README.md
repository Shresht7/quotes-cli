# `quotes`

A super simple CLI application to display inspirational quotes in the terminal.

## 📘 Usage

```sh
quotes --filepath ./quotes.csv --border "-" --border-color red
```

```
-------------------------------------------
Wise is the man who knows he knows nothing.
 -- Socrates
-------------------------------------------
```

### 📖 Help

```
Usage: quotes [SUBCOMMAND] [OPTIONS]

Subcommands:
  random                       Show a random quote
  get <id>                     Get a specific quote by ID
  help                         Show the help message
  version                      Show the version number

Options:
  -f, --filepath <path>        Path to the CSV file containing quotes (default: quotes.csv)
  -c, --color                  The text color
  --author-color               The color to use for the author
  -m, --margin <number>        The number of lines to leave as margin (default: 1)
  -b, --border <char>          Border character (default: '=')
  --border-color <color>       Color for the border (default: 'default')
  --no-borders                 Disables borders
  --no-color / --plain         Plain output

  -h, --help                   Show the help message
  -v, --version                Show the version number

Examples:
  quotes
  quotes random
  quotes --margin 2 --color cyan
```

## 📄 License

[MIT License](./LICENSE)
