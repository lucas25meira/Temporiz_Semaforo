/* Programa de capacitação EMBARCATECH
 * Unidade 4 - Microcontroladores / Capítulo 5 - Clock e os temporizadores do sistema
 * Tarefa 1 - Aula Síncrona 29/01/2025
 *
 * Programa desenvolvido por:
 *      - Lucas Meira de Souza Leite
 * 
 * Objetivos: 
 *      - Simular o funcionamento de um semáforo
 *      - Fazer uso da função 'add_repeating_timer_ms()' do Pico SDK
 *      - Fazer uso da função 'repeating_timer_callback()' do Pico SDK
 */

#include <stdio.h>
#include "pico/stdlib.h" 
#include "pico/time.h"   

#define LED_VERMELHO 13 // Definição do GPIO do LED vermelho
#define LED_AMARELO 12 // Definição do GPIO do LED azul
#define LED_VERDE 11 // Definição do GPIO do LED verde

volatile uint8_t cont = 1;

bool repeating_timer_callback(struct repeating_timer *t) { 
    if (cont == 1) {
        gpio_put(LED_VERMELHO, 1); //Seta o LED VERMELHO em HIGH
        gpio_put(LED_AMARELO, 0);
        gpio_put(LED_VERDE, 0);        
        cont++; //Incrementa o contador
    } else if (cont == 2) {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AMARELO, 1); //Seta o LED AMARELO em HIGH
        gpio_put(LED_VERDE, 0);        
        cont++; //Incrementa o contador
    } else if (cont == 3) {
        // Acende o LED verde e apaga os outros
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AMARELO, 0);
        gpio_put(LED_VERDE, 1); //Seta o LED VERDE em HIGH
        cont = 1; //Reseta o contador
    }
    return true; 
}

int main() {
    uint Tempo = 0; 
    stdio_init_all();  

    //Inicialização das GPIOs
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 1); // LED VERMELHO inicia aceso

    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_put(LED_AMARELO, 0);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);

    struct repeating_timer timer;

    // Chamada da função de callback
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {  //Rotina apenas para impressão de mensagem a cada 1 segundo
        Tempo++;
        sleep_ms(1000); 
        printf("Tempo decorrido: %d segundo(s)\n", Tempo);
    }
}