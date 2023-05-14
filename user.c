void saveUser(struct User user) {
    FILE *fp;
    fp = fopen("user_details.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(fp, "%s,%d,%s\n", user.name, user.age, user.email);

    fclose(fp);
}