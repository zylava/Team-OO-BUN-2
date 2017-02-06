#!/bin/bash

make 

echo -e "server {\n    listen 8080;\n}" > test_config
echo -e "\nconfig:"
cat test_config
echo ""

./webserver test_config & PID=$!


# response=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:8080)
# echo "HTTP response code is $response"

# content_type=$(curl -s -o /dev/null -w "%{content_type}" http://localhost:8080)
# echo "Content Type is $content_type"




echo ""

kill $PID

if [ $response == "200" ] && [ $content_type == "text/plain" ]; then
	echo "Success with exit code $?"
else
	echo "Fail with exit code $?"
fi

