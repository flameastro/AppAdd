# AppAdd

## Introduction

*AppAdd* is a free CLI tool that allows you to install *.appImages* files from a [specific appImages repository](https://github.com/flameastro/appImages). It's made just for Linux users

## How to install

Make sure you have the needed packages:

```bash
# For Debian/Ubuntu users
sudo apt update && sudo apt install git gcc make wget build-essential

# For Fedora users
sudo dnf install git gcc make wget build-essential

# For Arch users
sudo pacman -S git gcc make wget build-essential
```

Then clone the project:

```bash
git clone https://github.com/flameastro/AppAdd.git
cd AppAdd
```

Then execute the `make` command to compile all the project:

```bash
make
```

Then create a **Symbolic Link**:

```bash
sudo ln -s your/full/path/appadd /usr/local/bin/
```

Where `your/full/path/` is the path you are in, for example `~/Downloads/AppAdd/`

For example:
```bash
sudo ln -s ~/Downloads/AppAdd/appadd /usr/local/bin/appadd
```

So now you can use `appadd` in any directory of your computer.
