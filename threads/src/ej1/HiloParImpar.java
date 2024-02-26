package ej1;

public class HiloParImpar implements Runnable {
    private int tipo;

    public HiloParImpar(int tipo) {
        this.tipo = tipo;
    }

    @Override
    public void run() {
        if (tipo == 1) {
            for (int i = 2; i <= 100; i += 2) {
                System.out.println(Thread.currentThread().getName() + " generando número par " + i);
            }
        } else if (tipo == 2) {
            for (int i = 101; i <= 200; i += 2) {
                System.out.println(Thread.currentThread().getName() + " generando número impar " + i);
            }
        }
    }
}
