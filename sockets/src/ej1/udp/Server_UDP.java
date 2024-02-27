package ej1.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;

public class Server_UDP {

    private static final int ARRAY_SIZE = 1024;

    public static void main(String[] args) {
        byte[] array = new byte[ARRAY_SIZE];

        try (DatagramSocket datagramSocket = new DatagramSocket(3055)) {
            DatagramPacket datagramPacketFromClient1 = new DatagramPacket(array, ARRAY_SIZE);
            datagramSocket.receive(datagramPacketFromClient1);
            ByteBuffer wrapped = ByteBuffer.wrap(datagramPacketFromClient1.getData(), 0, datagramPacketFromClient1.getLength());
            int numFromClient1 = wrapped.getInt();

            // synchronization with client 2!
            DatagramPacket datagramPacketFromClient2 = new DatagramPacket(array, array.length);
            datagramSocket.receive(datagramPacketFromClient2);
            InetAddress client2IP = datagramPacketFromClient2.getAddress();
            int client2Port = datagramPacketFromClient2.getPort();
            byte[] bytes = ByteBuffer.allocate(4).putInt(numFromClient1).array();
            datagramSocket.send(new DatagramPacket(bytes,bytes.length, client2IP, client2Port));
            // receive result from client 2
            DatagramPacket datagramPacketResultOfClient2 = new DatagramPacket(array, array.length);
            datagramSocket.receive(datagramPacketResultOfClient2);
            // send result to client 1
            DatagramPacket datagramPacketForClient2 = new DatagramPacket(datagramPacketResultOfClient2.getData(),
                    datagramPacketFromClient1.getLength(), datagramPacketFromClient1.getAddress(), datagramPacketFromClient1.getPort());
            datagramSocket.send(datagramPacketForClient2);



        } catch (IOException ignored) {

        }

    }
}
