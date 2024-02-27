package ej1.tcp;

import java.io.IOException;

public class CalculatorClient extends Client{


    public CalculatorClient(String address, int port, int id) {
        super(address, port, id);
    }

    public static void main(String[] args) {
        CalculatorClient calculatorClient = new CalculatorClient("localhost", 3055, 2);
        try {
            calculatorClient.behaviour();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
    public int factorial(int n) {
        int fact = 1;
        for (int i = 2; i <= n; i++) {
            fact = fact * i;
        }
        return fact;
    }
    @Override
    public void behaviour() throws IOException, ClassNotFoundException {
        Information information = (Information) objectInputStream.readObject();
        int fact = factorial(information.number());
        Information informationT = new Information(id, information.sender(), fact);
        objectOutputStream.writeObject(informationT);
    }
}
