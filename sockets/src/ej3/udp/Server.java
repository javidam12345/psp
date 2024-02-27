package ej3.udp;


import ej2.utils.Converter;
import ej3.tcp.Bill;
import ej3.tcp.IVAType;
import ej3.tcp.Result;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.EnumMap;

public class Server {
    private static final EnumMap<IVAType, Double> IVAReferenceMap = new EnumMap<>(IVAType.class);

    public static double getIVA(IVAType ivaType) {
        return IVAReferenceMap.get(ivaType);
    }


    private static void setIVAValues() {
        IVAReferenceMap.put(IVAType.EUR, 21.0);
        IVAReferenceMap.put(IVAType.ESP, 45.32);
        IVAReferenceMap.put(IVAType.IGC, 5.0);
    }
    public static void main(String[] args) {
        setIVAValues();
        byte[]array = new byte[1024];
        try(DatagramSocket datagramSocket = new DatagramSocket(3055)){
            DatagramPacket datagramPacket = new DatagramPacket(array, array.length);
            datagramSocket.receive(datagramPacket);

            Bill bill = (Bill) Converter.convertBytesToObject(array);
            double IVA = ej3.udp.Server.getIVA(bill.IVAType());
            double total = bill.amount() + ((bill.amount() * IVA) / 100);
            Result result = new Result(IVA, total);
            byte[]resultOfBytes = Converter.createByteArrayOfObject(result);
            DatagramPacket datagramPacketToClient = new DatagramPacket(resultOfBytes, resultOfBytes.length, datagramPacket.getAddress(), datagramPacket.getPort());
            datagramSocket.send(datagramPacketToClient);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
