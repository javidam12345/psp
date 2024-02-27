package ej2.udp;

import ej2.utils.Converter;
import java.io.IOException;
import java.net.*;

public class UDP_Client {




    private static final String serverAddress = "localhost";

    private static final int port = 3055;

    public static void main(String[] args) {
        byte[]buffer = new byte[1024];
        try (DatagramSocket datagramSocket = new DatagramSocket()){
            int []array = new int[]{ 1, 2 ,3 ,4, 5 };
            byte[]arrayConvertedToBytes = Converter.createByteArrayOfObject(array);
            DatagramPacket datagramPacket = new DatagramPacket(arrayConvertedToBytes,
                    arrayConvertedToBytes.length, InetAddress.getByName(serverAddress), port);
            datagramSocket.send(datagramPacket);

            DatagramPacket datagramPacketWithResults = new DatagramPacket(buffer, buffer.length);
            datagramSocket.receive(datagramPacketWithResults);
            ej2.udp.ResultInformation resultInformation = (ResultInformation) Converter.convertBytesToObject(datagramPacketWithResults.getData());
            System.out.println(resultInformation);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
