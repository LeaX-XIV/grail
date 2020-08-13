void func() {
	char child_string[10];
	FILE* f = fopen
	unsigned int parent, child;
	list_t* child_list = malloc(sizeof *child_list);
	list_init(child_list, A_NUMBER);

	fscanf(f, "%u:", parent);

	fscanf(f, "%s", child_string);
	while(child_string[0] != '#') {
		child = atoi(child_string);
		list_append(child_list, child);	// Save in list
		fscanf(f, "%s", child_string);
	}

	// save the list in array
}