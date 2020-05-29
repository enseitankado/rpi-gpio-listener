# Service mode (no outputs)
sudo svc -d /service/listener/
sudo rm -rf /home/pi/bin/listener
echo "/service/listener/ durduruldu."
echo "/home/pi/bin/listener silindi."
g++ -o /home/pi/bin/listener gpio_listener.cpp -lwiringPi -lm -lssl -lcrypto -Ofast -s
echo "# /home/pi/bin/listener olusturuldu."
sudo svc -u /service/listener
echo "/service/listener/ baslatildi."
sudo svstat /service/listener

# Console mode (writes outputs to tty)
sudo rm -rf listener
g++ -o listener gpio_listener.cpp -lwiringPi -lm -lssl -lcrypto -Ofast -s -D CONSOLE_MODE=1
echo "# listener CONSOLE_MODE ile olusturuldu."
