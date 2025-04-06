### Nearest Neighbor Search using K-d Tree

Allows querying the closest point (e.g., restaurant or location) to a given latitude and longitude from a CSV dataset.

#### Cloning the repository

```bash
git clone https://github.com/KumaarBalbir/n-neighbor-kdtree.git
```

#### Usage

first go to the root directory of the project.

```bash
make clean && make
```
This will compile the program and create the `nearest_neighbor` executable in the `build` directory.

```bash
python3 client/client.py
```
This will run the client script, which will prompt you to enter a latitude and longitude.

press enter to use the default values of 3 and 4.

