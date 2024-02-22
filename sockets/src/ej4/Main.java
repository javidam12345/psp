package ej4;

public class Main {
    public static void main(String[] args) {
        long pid = ProcessHandle.current().pid();
        System.out.println(pid);
    }
}
