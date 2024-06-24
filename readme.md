# Minishell

A repository containing the minishell project of 42 Malaga. The aim of this project is to create a basic shell written in C that supports basic commands, pipes, redirections and has some basic builtings. This shell is compatible with Linux and MacOs. You can find all the information about the project in the subject pdf.

## Authors

- [@juan-est145](https://www.github.com/juan-est145)
- [@MiguelAngel456](https://www.github.com/MiguelAngel456)

## Dependencies
In order to be able to compile this project, you will need a C compiler and the readline library. If you do not have this library, you can install it like this.

Debian distributions
```bash
sudo apt update
sudo apt install libreadline-dev 
```
MacOS
```bash
brew install readline
```

The project has not been tested in MacOS, so I cannot guarantee to a 100% that it will compile, but in case there is any error, it must be because of the dependencies.

## Run Locally

Clone the project

```bash
  git clone https://github.com/juan-est145/minishell.git
```

Go to the project directory

```bash
  cd minishell
```

Compile the project
```bash
  make
```

Run the project
```bash
  ./minishell
```

To delete the .o files and the executable
```bash
  make fclean
```