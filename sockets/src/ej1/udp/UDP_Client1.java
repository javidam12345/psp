package ej1.udp;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Scanner;

public class UDP_Client1 {
    public static void main(String[] args) {

        try(DatagramSocket datagramSocket = new DatagramSocket())
        {
            byte[] bytes = ByteBuffer.allocate(4).putInt(10).array();
            DatagramPacket datagramPacket = new DatagramPacket(bytes, bytes.length, InetAddress.getByName("localhost"), 3055);
            datagramSocket.send(datagramPacket);
            // receive result from server
            datagramSocket.receive(datagramPacket);
            ByteBuffer wrapped = ByteBuffer.wrap(datagramPacket.getData(), 0, datagramPacket.getLength());
            System.out.println("Result of query: "+wrapped.getInt());

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
