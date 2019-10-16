# Jupyter notebooks for BlasBooster

If you haven't done yet, please install [docker](https://docs.docker.com/install/) first.

```bash
docker build -f dockerfile-cpu -t braintwister/blasbooster:<version> .
docker run -it -p 8888:8888 braintwister/blasbooster:<version>
```

For using a host GPU card within a docker container,
[nvidia-docker](https://github.com/NVIDIA/nvidia-docker) must be installed and
the runtime attribute must be set to nvidia. 

```bash
docker build -f dockerfile-gpu -t braintwister/blasbooster:<version>-gpu .
docker run --runtime=nvidia -it -p 8888:8888 braintwister/blasbooster:<version>-gpu
```

The link to the jupyter server will be printed in the end of the running docker
container output.  
