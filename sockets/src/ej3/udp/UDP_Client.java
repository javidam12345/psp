package ej3.udp;

import ej2.utils.Converter;
import ej3.tcp.Bill;
import ej3.tcp.IVAType;
import ej3.tcp.Result;

import java.io.IOException;
import java.net.*;

public class UDP_Client {

    private static final int BUFFER_SIZE = 1024;
    private static final String serverAddress = "localhost";
    private static final int serverPort = 3055;
    public static void main(String[] args) {
        byte[]buffer = new byte[BUFFER_SIZE];
        try(DatagramSocket datagramSocket = new DatagramSocket())
        {
            Bill bill = new Bill("19934-F", "28/11/2003", 300, IVAType.ESP);
            byte[]informationBytes = Converter.createByteArrayOfObject(bill);
            DatagramPacket datagramPacket = new DatagramPacket(informationBytes, informationBytes.length, InetAddress.getByName(serverAddress), serverPort);
            datagramSocket.send(datagramPacket);
            DatagramPacket datagramPacketResult = new DatagramPacket(buffer, buffer.length);
            datagramSocket.receive(datagramPacketResult);
            Result result = (Result) Converter.convertBytesToObject(datagramPacketResult.getData());
            System.out.printf("Result:  "+result.IVA() + " | "+result.total());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
