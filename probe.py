#!/usr/bin/python3
# Modbus TCP pushbutton test reader

# Input: Network, mDNS, Modbus TCP
# Output: terminal, exit status

import socket
import struct


class Node(object):
    def __init__(self, ip):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((ip, 502))

    def close(self):
        self.socket.close()

    def qa(self, query, length):
        self.socket.send(query)
        answer = self.socket.recv(length)
        return answer

    def rdi(self, a, n):
        """ read discrete inputs """
        unpack = '!HHHBBB' + 'B' * n
        unpack_length = struct.calcsize(unpack)
        query = struct.pack('!HHHBBHH', 0, 0, 6, 255, 2, a, n)
        print('# tx ' + query.hex(' ') + ' (%d)' % len(query))
        answer = self.qa(query, unpack_length)
        print('# rx ' + answer.hex(' ') + ' (%d)' % len(answer))
        rn = struct.unpack(unpack, answer)
        return rn[-1]


node = Node('mpb.local')
reg = node.rdi(100, 1)
node.close()
exit(reg)
