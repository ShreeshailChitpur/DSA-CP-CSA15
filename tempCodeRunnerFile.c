

void display_inventory() {
    printf("Inventory:\n");
    for (int i = 0; i < num_items; i++) {
        printf("%s\t%d\t$%.2f\n", items[i].name, items[i].quantity, items[i].price);
    }
}
int main(){
    add_item();
    add_item();
    display_inventory();
}
