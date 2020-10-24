# FSeam_Tutorial
Simple tutorial about how to use FSeam.  
Find the explanation of the tuto on the [FyS blog](http://freeyoursoul.online)

## Alternatively: run the examples using Docker

```bash
# Go inside this folder
cd FSeam_tutorial;

# Run the docker:
docker run --rm -d -t --privileged --name fseam  -v `pwd`:/app  cometurrata/fseam:latest bash;

# Open an interactive terminal into the running docker
docker exec -it -w /app fseam bash;

# Just run the commands like you would on your own bash
cmake -DFSEAM_USE_CATCH2=ON ./ ;
make all -j$(nproc);
make test;
```
