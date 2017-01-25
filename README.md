# TEAM-OO-BUN-2

Implementation of the echo server was done using the Boost Documentation Examples. 
[Boost documentation](http://www.boost.org/doc/libs/1_62_0/doc/html/boost_asio/examples/cpp11_examples.html#boost_asio.examples.cpp11_examples.spawn)

## Usage

1. Clone the repository:
```
git clone --recursive https://github.com/UCLA-CS130/Team-OO-BUN-2.git
```
2. Change directory into the webserver directory
```
cd Team-OO-BUN-2/echo_server/webserver/
```

3. Make
```
make
```

4. Rune the server
```
./webserver <config>
```
Our default <config> file is called `config`

5. Open browser (Chrome, Firefox, etc.) and go to localhost:<port>. Note that the config file defines the port number as `8080`
