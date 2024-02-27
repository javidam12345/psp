package ej3.udp;

import javax.xml.crypto.Data;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class Server {
    public static void main(String[] args) {
        try(DatagramSocket datagramSocket = new DatagramSocket()){
            //DatagramPacket datagramPacket = new DatagramPacket();
            //datagramSocket.send();
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }
    }
}
