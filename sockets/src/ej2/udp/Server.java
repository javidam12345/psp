package ej2.udp;

import ej2.udp.ResultInformation;
import ej2.utils.Converter;

import java.io.IOException;

import java.net.DatagramPacket;
import java.net.DatagramSocket;


public class Server {

    private static final int ARRAY_SIZE = 1024;



    private static ResultInformation getInformationFromArray(int[] array) {
        int total = 0;
        int biggest = array[0];
        int smallest = array[0];
        for (int j = 0; j < array.length; j++) {
            if (array[j] > biggest) {
                biggest = array[j];
            } else if (array[j] < smallest) {
                smallest = array[j];
            }
            total += array[j];
        }
        return new ResultInformation(total, biggest, smallest);

    }



    public static void main(String[] args) {
        byte[]array = new byte[ARRAY_SIZE];
        try(DatagramSocket datagramSocket = new DatagramSocket(3055))
        {
            DatagramPacket datagramPacket = new DatagramPacket(array, array.length);
            datagramSocket.receive(datagramPacket);
            // https://stackoverflow.com/questions/11437203/how-to-convert-a-byte-array-to-an-int-array
            int[]arrayOfQuery = (int[]) Converter.convertBytesToObject(array);
            ej2.udp.ResultInformation resultInformation = getInformationFromArray(arrayOfQuery);
            byte[]informationBytes = Converter.createByteArrayOfObject(resultInformation);
            datagramSocket.send(new DatagramPacket(informationBytes, informationBytes.length,
                    datagramPacket.getAddress(), datagramPacket.getPort()));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
