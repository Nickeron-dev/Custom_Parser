#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

const char *ERROR_SSL_MESSAGE = "SSL peer certificate or SSH remote key was not OK";

int main(int argc, char *argv[])
{
	CURL *curl;
	CURLcode result;

	if(argc != 2) {
		printf("Usage: %s URL\n", argv[0]);
		return EXIT_FAILURE;
	}

	curl = curl_easy_init();

	printf("SITE: %s\n", argv[1]);
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
  
	FILE *output_file = fopen("index.html", "w");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);
	
    result = curl_easy_perform(curl);
    if(result != CURLE_OK)
    {
		if (strcmp(curl_easy_strerror(result), ERROR_SSL_MESSAGE) == 0)
		{
			printf("Retry without ssl verifiers...\n");
		    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
			curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);
		}
		else
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(result));
			exit(EXIT_FAILURE);
		}
	}
	
	result = curl_easy_perform(curl);
	
    if(result != CURLE_OK)
    {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(result));
		exit(EXIT_FAILURE);
	}
	
	curl_easy_cleanup(curl);
	fclose(output_file);
	printf("Success!!!");
	return EXIT_SUCCESS;
}
