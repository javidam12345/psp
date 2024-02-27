package ej3.tcp;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.EnumMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server {

    private final ExecutorService executorService = Executors.newFixedThreadPool(20);
    private static final EnumMap<IVAType, Double> IVAReferenceMap = new EnumMap<>(IVAType.class);


    public Server(){
        setIVAValues();
    }

    public static double getIVA(IVAType ivaType) {
        return IVAReferenceMap.get(ivaType);
    }
    private void setIVAValues() {
        IVAReferenceMap.put(IVAType.EUR, 21.0);
        IVAReferenceMap.put(IVAType.ESP, 45.32);
        IVAReferenceMap.put(IVAType.IGC, 5.0);
    }

    public void start() {
        try (ServerSocket serverSocket = new ServerSocket(3055)) {
            while(true) {
                Socket socket = serverSocket.accept();
                executorService.submit(new ClientHandler(socket));
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new Server().start();
    }
}
