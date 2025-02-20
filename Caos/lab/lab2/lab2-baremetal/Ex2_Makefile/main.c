extern void delay_routine_1(void);
extern void delay_routine_2(unsigned int delay_counter);

int main(){

    int delay_value = 5;
    delay_routine_2(delay_value);

    return 0;
}