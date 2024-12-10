# Create a Snap for an OpenVINO GenAI application

This is a very basic example for building a snap for an OpenVINO GenAI C++ application.

More information:
- https://snapcraft.io/
- https://ubuntu.com/tutorials/create-your-first-snap

## Limitations

This example currently only works for OpenVINO inference on CPU.

## Prerequisites

Clone this repository and download and uncompress the OpenVINO GenAI archive. This example uses OpenVINO 2024.5. For other OpenVINO
versions, change CMakeLists.txt to match.

Step-by-step for Ubuntu 24.04 (For Ubuntu 20.04 or 22.04 replace ubuntu24 with ubuntu20/ubuntu22):

```shell
git clone https://github.com/helena-intel/openvino-genai-snap-example.git
cd openvino-genai-snap-example
curl -O https://storage.openvinotoolkit.org/repositories/openvino_genai/packages/2024.5/linux/openvino_genai_ubuntu24_2024.5.0.0_x86_64.tar.gz
tar zxvf openvino_genai_ubuntu24_2024.5.0.0_x86_64.tar.gz
mv openvino_genai_ubuntu24_2024.5.0.0_x86_64 openvino_genai
```

## Build the snap

Run the following command in the `openvino-genai-snap-example` directory

```shell
snapcraft
```

## Install the snap

The `--dangerous` flag is needed because the app isn't signed by the Snap Store.
See the [Create your first snap](https://ubuntu.com/tutorials/create-your-first-snap) tutorial (section 6 and 7).

```shell
sudo snap install --dangerous openvinodemo_0.1_amd64.snap
```

You can copy this snap to another Ubuntu 24.04 machine, and install and run it there without configuring or installing anything.

## Run the demo

```
./openvinodemo modelpath prompt CPU
```
