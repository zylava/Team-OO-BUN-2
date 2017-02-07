#!/bin/bash

make 

port=1080

# echo -e "server {\n    listen $port;\n}" > test_config
# echo -e "\nconfig:"
# cat test_config
# echo ""

echo -e "port 1080;\n" > test_config
echo -e "path /echo EchoHandler {\n    placeholder;\n}" >> test_config
echo -e "path /static StaticFileHandler {\n    root \"static\";\n}" >> test_config

echo -e "\nconfig:"
cat test_config

./webserver test_config & PID=$!


# response=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8080)
# echo "HTTP response code is $response"

# content_type=$(curl -s -o /dev/null -w "%{content_type}" http://localhost:8080)
# echo "Content Type is $content_type"

curl -s -I http://localhost:$port/static/index.html > /tmp/actual

kill $PID

diff testdata/expected /tmp/actual

if [ $? == 0 ]; then
	echo "Success with exit code $?"
else
	echo "Fail with exit code $?"
fi



# echo ""

# if [ $response == "200" ] && [ $content_type == "text/plain" ]; then
# 	echo "Success with exit code $?"
# else
# 	echo "Fail with exit code $?"
# fi

