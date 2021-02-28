import socket
from config import CONTROL_IP, CONTROL_PORT

sk = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
sk.settimeout(3000)
sk.sendto("0 0".encode('ascii'), (CONTROL_IP, CONTROL_PORT))
