void func() {
	char child_string[10];
	unsigned int parent, child;
	list_t* child_list = malloc(sizeof child_list);
	list_init(child_list, A_NUMBER);

	fscanf(FILE, "%u:", parent);

	fscanf(FILE, "%s", child_string);
	while(child[0] != '#') {
		child = atoi(child_string);
		list_append(child_list, child);	// Save in list
		fscanf(FILE, "%s", child_string);
	}

	// save the list in array
}