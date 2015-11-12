#### Build Third Party Libraries
HOTBOX has dependency on third party libraries. You need to build third party
libraries the first time using Hotbox. Afterwards you can skip this part even
when you rebuild Hotbox. Two ways to get third party libraries:

##### With Sudo
If you have `sudo` access, you can install many third party libraries using
```
# Under repo root path:
sudo apt-get update && sudo apt-get -y install libgflags-dev  \
libgoogle-glog-dev libgoogle-perftools-dev libsnappy-dev libyaml-cpp-dev \
libboost1.55-dev libboost-filesystem1.55-dev unzip \
python-setuptools autoconf python-zmq python-yaml

# Compile just the non-standard third party libraries to [build_path].
python install_third_party.py [build_path]
```
where `[build_path]` needs to be replaced by a path you put dependencies into
and with write permission. For example, to build it as `third_party` under
hotbox repo path, do
```
python install_third_party.py third_party
```

##### Without Sudo
If you can not run `sudo apt-get` then do
```
# Compile just the non-standard third party libraries to [build_path].
python install_third_party.py [build_path] build_all
```
You will compile all the dependencies to `[build_path]`. For example
```
python install_third_party.py third_party build_all
```


#### Build Hotbox
The rest of the commands assume you are in repo root. Before building,
configure `THIRD_PARTY_PATH` in `config.mk'. By default it is
```
THIRD_PARTY = $(PROJECT)/third_party
```
After that, run
```
make -j4
```
Run the command again if you get error the first time. To test run it:
```
# Remove any existing test db from previous runs.
rm -r db_testbed/

# Start server
python ./script/run_db_server.py

# Ingest a toy dataset to test_db. This ingest ‘test/resource/dataset/a1a.toy’
# to test_db. Check that both server and client outputs sensible messages.
python python/db/db_client.py

# Run the C++ client to read transformed data. This uses transform in
# ‘test/resource/select_transform.conf’
$ python script/run_hotbox_client.py
```
You should see output like:
```
I1108 23:45:30.081626 28463 hotbox_client_main.cpp:31] sparse dim: 108 label:
0 weight: 1 | 3:1 11:1 14:1 19:1 39:1 42:1 55:1 64:1 67:1 73:1 75:1 76:1 80:1
83:1 106:1
I1108 23:45:30.081643 28463 hotbox_client_main.cpp:31] sparse dim: 108 label:
0 weight: 1 | 3:1 6:1 17:1 27:1 35:1 40:1 57:1 63:1 69:1 73:1 74:1 76:1 81:1
103:1 106:1
I1108 23:45:30.081656 28463 hotbox_client_main.cpp:31] sparse dim: 108 label:
0 weight: 1 | 4:1 6:1 15:1 21:1 35:1 40:1 57:1 63:1 67:1 73:1 74:1 77:1 80:1
83:1 105:1
I1108 23:45:30.081670 28463 hotbox_client_main.cpp:31] sparse dim: 108 label:
1 weight: 1 | 5:1 6:1 15:1 22:1 36:1 41:1 47:1 66:1 67:1 72:1 74:1 76:1 80:1
83:1 105:1
I1108 23:45:30.081683 28463 hotbox_client_main.cpp:31] sparse dim: 108 label:
0 weight: 1 | 2:1 6:1 16:1 22:1 36:1 40:1 54:1 63:1 67:1 73:1 75:1 76:1 80:1
83:1 105:1
```
