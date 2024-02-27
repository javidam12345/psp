package ej1.udp;

import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;

public class UDP_Client2 {

    private static final int ARRAY_SIZE =  1024;


    private static int factorial(int num) {
        if (num == 0) return 1;
        int total = 1;
        for (int i = num; i > 1; i--)
            total *= i;
        return total;
    }

    private static final String serverIp ="localhost";

    private static final int serverPort = 3055;

    public static void main(String[] args) {
        byte[]array = new byte[ARRAY_SIZE];

        try(DatagramSocket datagramSocket = new DatagramSocket())
        {
            DatagramPacket datagramPacket = new DatagramPacket(array, array.length, InetAddress.getByName(serverIp), serverPort);
            // salute!
            datagramSocket.send(datagramPacket);
            // wait for number to calculate
            datagramSocket.receive(datagramPacket);
            ByteBuffer wrapped = ByteBuffer.wrap(datagramPacket.getData(), 0, datagramPacket.getLength());
            int numToCalculate  = wrapped.getInt();
            byte[] bytes = ByteBuffer.allocate(4).putInt(factorial(numToCalculate)).array();
            datagramPacket = new DatagramPacket(bytes, bytes.length, InetAddress.getByName("localhost"), 3055);
            datagramSocket.send(datagramPacket);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
