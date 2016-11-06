
CONFIG_PATH="src/config.json"

.PHONY: build

build: build_socketio_cpp
	git submodule update --init --recursive
	mkdir -p build
	rm -f config/gazebo/models/x340/x340.sdf
	cd build; cmake ..; make

server:
	node ./src/server

run: build
	./build/gcs $(CONFIG_PATH)

test: build
	cd build; ./test_tansa # make test

clean:
	rm -rf build
	rm -rf build_firmware
	rm -rf build_socketio_cpp
	rm -rf lib/socket.io-client-cpp/build
	rm -rf tmp



# Build the included firmware for the purpose of simulation
build_firmware:
	git submodule update --init --recursive
	mkdir -p build_firmware
	cd build_firmware; cmake ../lib/Firmware -DCONFIG="posix_sitl_default"; make; make sitl_gazebo

# Starts an empty sim
sim: build_firmware build
	./scripts/start_gazebo.sh


build_socketio_cpp:
	git submodule update --init --recursive
	mkdir -p build_socketio_cpp
	cd build_socketio_cpp; cmake ../lib/socket.io-client-cpp -DCMAKE_CXX_FLAGS="-fPIC"; make install
