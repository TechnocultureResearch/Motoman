# motoman
***Moto***rs ***Man***ager CLI


[![Tests](https://github.com/TechnocultureResearch/MotorsManager-CLI/actions/workflows/python-package.yml/badge.svg?branch=dev)](https://github.com/TechnocultureResearch/MotorsManager-CLI/actions/workflows/python-package.yml)
[![TestPyPi](https://github.com/TechnocultureResearch/MotorsManager-CLI/actions/workflows/python-publish.yml/badge.svg)](https://github.com/TechnocultureResearch/MotorsManager-CLI/actions/workflows/python-publish.yml)

A command line tool to control a set of stepper motors. Intended to serve the specific needs of Microfabricator T.

# Usage
<img width="645" alt="Screenshot 2021-03-15 at 2 27 23 AM" src="https://user-images.githubusercontent.com/33483920/111083938-1dd29400-8536-11eb-99e8-800182b5d991.png">

```bash
python motoman.py
```

# Install

## Requirements
- Python 3.7 (or later)
- pip
- poetry

## Using pip
```bash
pip install --index-url https://test.pypi.org/simple/ --extra-index-url https://pypi.org/simple motoman
```

# More on Usage
## verbose mode
```bash
python motoman.py -v
```
or
```bash
python motoman.py --verbose
```
