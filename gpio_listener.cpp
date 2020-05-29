#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	int pin = 0;
	char cmd[100];
	char gpio[] = {1,4,5,6,21,22,23,24,25,26,28,29};
	char gpio_last[sizeof(gpio)];

	// Open the GPIO devices and allows our program to access it
	wiringPiSetup();

	// Set pullup resistors and pin modes
	for ( pin = 0; pin < sizeof(gpio); pin++) {
		pullUpDnControl( gpio[ pin ], PUD_UP);
		pinMode( gpio[ pin ], INPUT);
		gpio_last[ pin ] = 1;
	}

	#ifdef CONSOLE_MODE
	cout << "Listening..." << endl;
	#endif
	while (1) {
		usleep(0.05 * 1000 * 1000);
		for ( pin = 0; pin < sizeof(gpio); pin++) {

			if ( digitalRead( gpio[ pin ] ) == 0 )
				gpio_last[ pin ] = 0;

			else if (gpio_last[ pin ] == 0) {

				#ifdef CONSOLE_MODE
				printf("GPIO.%d is pressed.\n", gpio[ pin ]);
				#endif

				sprintf(cmd, "php -f /home/pi/bin/exec.php %i", gpio[ pin ]);
				system(cmd);

				gpio_last[ pin ] = 1;
			}
		}
	}
}
