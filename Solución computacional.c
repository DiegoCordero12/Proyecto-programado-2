  printf("\t1. Modificar \n");
    printf("\t2. Eliminar\n");//eliminar queda pendiente
    printf("\t3. Ver\n");
    printf("\t4. Atras\n");
}

void menu2(){//menu ciberdelincuentes
    printf("|================CIBERDELINCUENTES==================|\n");
    printf("\t1. Modificar\n");
    printf("\t2. Eliminar\n");//eliminar queda pendiente
    printf("\t3. Ver\n");
    printf("\t4. Atras\n");
}

void menu3(){//menu paises
    printf("|================PAISES==================|\n");
    printf("\t1. Insertar\n");
    printf("\t2. Modificar\n");
    printf("\t3. Eliminar\n");
    printf("\t4. Inorden\n");
    printf("\t5. Jerarquia\n");
    printf("\t6. Atras\n");
}

void menuPrincipal(){//menu principal del sistema
    printf("|================BIENVENIDO AL SISTEMA DE CIBERSEGURIDAD==================|\n");
    printf("\t1. Tipos ciberataques\n");
    printf("\t2. Ciberdelincuente\n");
    printf("\t3. Informacion de paises\n");
    printf("\t4. Gestion de informacion de ciberataques\n");
    printf("\t5. Registro de mensaje de seguridad de notificacion de ciberataque\n");
    printf("\t6. Simulacion de ciberataques\n");
    printf("\t7. Obtener rutas de ciberataques\n");
    printf("\t8. Analisis de datos\n");
    printf("\t9. Salir\n");
}

//ALMACENAMIENTO DE INFO DE PAISES

typedef struct ArbolPaises {//tipo de dato de los paises
    int codigo;
    char nombre[25];
    int habitantes;
    char continente[25];
    struct ArbolPaises *left;
    struct ArbolPaises *right;
}ArbolPaises;

ArbolPaises* raiz = NULL;

ArbolPaises* nuevaHoja(int codigo, char nombre[], int habitantes, char continente[]) {//crear un node pais
    ArbolPaises* node = (ArbolPaises*) malloc(sizeof(ArbolPaises));

    node->codigo = codigo;
    strcpy(node->nombre, nombre);
    node->habitantes = habitantes;
    strcpy(node->continente, continente);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insertarHoja(ArbolPaises* node, int codigo, char nombre[], int habitantes, char continente[]) {//insertar un pais en el arbol
    if(node == NULL){
        raiz = nuevaHoja(codigo, nombre, habitantes, continente);
    }
    else if (codigo > node->codigo) {//primero a la derecha
        if (node->right == NULL) {
            node->right = nuevaHoja(codigo, nombre, habitantes, continente);
        } else {
            insertarHoja(node->right, codigo, nombre, habitantes, continente);//recursividad
        }
    } else {
        if (node->left == NULL) {//si no a la izquierda
            node->left = nuevaHoja(codigo, nombre, habitantes, continente);
        } else {
            insertarHoja(node->left, codigo, nombre, habitantes, continente);//recursividad
        }
    }
}

void modificarPais(ArbolPaises* node, int codigo){//modificar un pais, debe ingresar un codigo de pais
    if(node == NULL){
        printf("Codigo no encontrado!");
        return;
    }
    else if(node->codigo == codigo){//cuando se encuentre
        printf("Ingrese el node codigo del pais: ");
        scanf("%d", &node->codigo);
        printf("Ingrese el node nombre del pais: ");
        scanf("%s", &node->nombre);
        printf("Ingrese la nueva cantidad de habitantes: ");
        scanf("%d", &node->habitantes);
        printf("Ingrese el node continente: ");
        scanf("%s", &node->continente);
        printf("Modificado con exito!");
        getchar();
        getchar();
    }
    else if(codigo < node->codigo){
        modificarPais(node->left, codigo);
    }
    else{
        modificarPais(node->right, codigo);
    }
}

ArbolPaises* minimo( ArbolPaises* node){//para encontrar la menor hoja del arbol 
    ArbolPaises* actual = node;
    while (actual && actual->left) {
        actual = actual->left;
    }
    return actual;
}

ArbolPaises* eliminarHoja(ArbolPaises* node, int codigo){//eliminar un pais del arbil
    if (node == NULL)
        return node;
    if (codigo < node->codigo)//se busca por la izquierda
        node->left = eliminarHoja(node->left, codigo);
    else if (codigo > node->codigo)//se busca por la derecha
        node->right = eliminarHoja(node->right, codigo);
    else{
        if (node->left == NULL) {
            ArbolPaises* aux = node->right;
            free(node);
            return aux;
        }
        else if (node->right == NULL) {
            ArbolPaises* aux = node->left;
            free(node);
            return aux;
        }
        ArbolPaises* aux = minimo(node->right);//se busca la hoja menor para reacomodar el arbol en caso de eliminar un nodo padre
        node->codigo = aux->codigo;
        node->right = eliminarHoja(node->right, aux->codigo);
    }
}

void inorden(ArbolPaises* node){
    if (node != NULL) {
        inorden(node->left);
        printf("Codigo: %d\n", node->codigo);
        printf("Nombre: %s\n", node->nombre);
        printf("Habitantes: %d\n", node->habitantes);
        printf("Continente: %s\n", node->continente);
        printf("------------------\n");
        inorden(node->right);
    }
}

void jerarquia(ArbolPaises* node, int primero, int count){
	int i = 0;
    if(node!=NULL){
        if(node == raiz){//para imprimir la raiz
            printf("\tCodigo: %d , Nombre: %s, Habitantes: %d, Continente: %s\n", node->codigo, node->nombre, node->habitantes, node->continente);
        }
        //se imprimen los hijos si tienen
        if(node->left != NULL){
            for( i = 0; i < count; i++){
                printf("\t");
            }
            printf("Codigo: %d, Nombre: %s, Habitantes: %d, Continente: %s\n", node->left->codigo, node->left->nombre, node->left->habitantes, node->left->continente);
            jerarquia(node->left, 0, count + 1);//recursividad
        }
        if(node->right != NULL){
            for(i = 0; i < count; i++){
                printf("\t");
            }
            printf("Codigo: %d, Nombre: %s, Habitantes: %d, Continente: %s\n", node->right->codigo, node->right->nombre, node->right->habitantes, node->right->continente);
            jerarquia(node->right, 0, count + 1);//recursividad
        }
    }
}

typedef struct TipoCiberataque{//lista simple para los tipos
    int codigoAtaque;
    char nombreAtaque[25];
    char descripcionAtaque[30];
    char canalesDeAtaque[3][25];
    struct TipoCiberataque *siguiente;
}TipoCiberataque;

TipoCiberataque* primerTipo = NULL;
TipoCiberataque* ultimoTipo = NULL;

//insertar tipo en la lista 
void insertarTipoCiberAtaque(int codigoAtaque, char* nombreAtaque, char* descripcionAtaque, char* canalesDeAtaque[]){
	int i = 0;
    TipoCiberataque* node = (TipoCiberataque*) malloc(sizeof(TipoCiberataque));
    node->codigoAtaque = codigoAtaque;
    strcpy(node->nombreAtaque, nombreAtaque);
    strcpy(node->descripcionAtaque, descripcionAtaque);
    for ( i = 0; i < 3; i++){
        strcpy(node->canalesDeAtaque[i], canalesDeAtaque[i]);
    }
    if(primerTipo == NULL){
        primerTipo = node;
        primerTipo->siguiente = NULL;
        ultimoTipo = node;
    }
    else{
        ultimoTipo->siguiente = node;
        node->siguiente = NULL;
        ultimoTipo = node;
    }
}

//modificar un tipo
void modificarTipoCiberataque(){   
    TipoCiberataque* aux = primerTipo;
    int codigoAtaque = 0;
    printf("Ingrese el codigoAtaque del tipo: ");
    scanf("%d", &codigoAtaque);
    while (aux != NULL){
        if(aux->codigoAtaque == codigoAtaque){
            printf("Ingrese el nuevo nombre: ");
            scanf("%s", &aux->nombreAtaque);
            printf("Ingrese la nueva descripcion: ");
            scanf("%s", &aux->descripcionAtaque);
        }
        aux = aux->siguiente;
    }
}

//mostrar los tipos
void mostrarTiposDeCiberataques(){
    TipoCiberataque* aux = primerTipo;
    printf("===========================\n");
    while (aux != NULL){
        printf("Codigo: %d\n", aux->codigoAtaque);
        printf("Nombre: %s\n", aux->nombreAtaque);
        printf("Descripcion: %s\n", aux->descripcionAtaque);
        int i = 0;
        printf("Canales: \n");
        while (i < 3) {
            printf("\t%s\n", aux->canalesDeAtaque[i]);
            i++;
        }
        printf("============================\n");
        aux = aux->siguiente;   
    }
    getchar();
    getchar();
}

//ALMACENAMIENTO DE CIBERDELINCUENTES
//Estructura de los ciberdelincuentes
typedef struct ListaCiberdelincuente{
    int id;
    char grupo[25];
    char paisorigen[30];
    char ataques[3][25];
    struct ListaCiberdelincuente *siguiente;
}ListaCiberdelincuente;

ListaCiberdelincuente* primerCiberdelincuente = NULL;
ListaCiberdelincuente* ultimoCiberdelincuente = NULL;

//Metodo para la insercion del ciberdelincuente
void insertarCiberdelinciente(int id, char* grupo, char* paisorigen, char* ataques[]){
	int i = 0;
    ListaCiberdelincuente* node = (ListaCiberdelincuente*) malloc(sizeof(ListaCiberdelincuente));
    node->id = id;
    strcpy(node->grupo, grupo);
    strcpy(node->paisorigen, paisorigen);
    for (i = 0; i < 3; i++){
        strcpy(node->ataques[i], ataques[i]);
    }
    if(primerCiberdelincuente == NULL){
        primerCiberdelincuente = node;
        primerCiberdelincuente->siguiente = NULL;
        ultimoCiberdelincuente = node;
    }
    else{
        ultimoCiberdelincuente->siguiente = node;
        node->siguiente = NULL;
        ultimoCiberdelincuente = node;
    }
}

//metodo para la modificacion de un CD
void modificarCiberdelincuente(){   
    ListaCiberdelincuente* aux = primerCiberdelincuente;
    int id = 0;
    printf("Ingrese el identificador: ");
    scanf("%d", &id);
    while (aux != NULL){
        if(aux->id == id){
            printf("Ingrese el nuevo grupo: ");
            scanf("%s", &aux->grupo);
            printf("Ingrese el nuevo pais de origen: ");
            scanf("%s", &aux->paisorigen);
        }
        aux = aux->siguiente;
    }
}

//metodo para la consulta de un CD
void consultarCiberdelincuentes(){
    ListaCiberdelincuente* aux = primerCiberdelincuente;
    printf("=============================\n");
    while (aux != NULL){
        printf("Identificador: %d\n", aux->id);
        printf("Grupo: %s\n", aux->grupo);
        printf("Pais de origen: %s\n", aux->paisorigen);
        int i = 0;
        printf("Ataques mas reconocidos: \n");
        while (i < 3){
            printf("\t%s\n", aux->ataques[i]);
            i++;
        }
        printf("============================\n");
        aux = aux->siguiente;   
    }
    getchar();
    getchar();
}







// Comienza la parte con grafos 







typedef struct Lista Lista;
typedef struct Nodo Nodo;

struct Nodo
{
	char dato[10000];
	Nodo *siguiente;
};

struct Lista
{
	Nodo *inicio;
};
Lista *listaNueva(void);
void insertarDato(Lista *L, char dato[10000]);
void mostrarLista(const Lista *L);
int listaVacia(Lista *L);
void liberarLista(Lista *L);

/*
listaNueva
Entrada:
Salida: una lista

*/
Lista *listaNueva(void)
{
	Lista *L;
	L = (Lista *) malloc(sizeof(Lista));
	L->inicio = NULL;
	return L;
}
/*
liberarLista
Entrada: una lista enlazada
Salida: la lista vacia

*/
void liberarLista(Lista *L)
{
	Nodo *n, *aux;
	if(L->inicio == NULL)
		return;
	if(L->inicio->siguiente == NULL)
		return;		
	n = L->inicio;
	
	while(n != NULL)
	{
		aux = n;
		n = n->siguiente;
		free(aux);
	}
	
}
/*
insertarDato
Entrada: una lista
Salida: un elemento nuevo a la lista

*/
void insertarDato(Lista *L, char dato[10000])
{
	Nodo *n, *aux;
	int i;
	if(L->inicio == NULL) //Valida si la lista está vacía
	{
		//Inserta al inicio de la lista
		L->inicio = (Nodo *) malloc(sizeof(Nodo));
		for(i=0;i<1000;i++){
			L->inicio->dato[i] = dato[i];
		}
		L->inicio->siguiente = NULL;
		return;
	}
	n = L->inicio;
	while(n!= NULL)
	{
		aux = n;
		n = n->siguiente;		
	}
	aux->siguiente = (Nodo *) malloc(sizeof(Nodo));
	aux->siguiente->siguiente = NULL;
	for(i=0;i<1000;i++){
			aux->siguiente->dato[i] = dato[i];
		}
	
}
/*
listaVacia
Entrada: una lista
Salida: comprueba si esta vacia

*/
int listaVacia(Lista *L)
{
	if(L->inicio == NULL)
		return 1;
	else
		return 0;
}
/*
mostrarLista
Entrada: una lista
Salida: la lista impresa con los daatos

*/
void mostrarLista(const Lista *L)
{
	Nodo *i;
	printf("La lista es: \n");
	for(i = L->inicio; i!= NULL; i = i->siguiente)
		printf("%s ", i->dato);
	printf("\n");
}



typedef struct Node Node;
typedef struct Arista Arista;
typedef struct ListaAdyacencia ListaAdyacencia;
typedef struct Grafo Grafo;

struct Node{
	char dato[100];
	char codigo[100];
	char codigoPostal[100];
	Node *siguiente;
	Arista *adyacencia;
	int visitado;
	int terminado;
	int monto;
	char anterior[100];
};

struct Arista
{
	Node *vertice;
	Arista *siguente;
	int peso;
};


struct Grafo{
	Node *inicio ;	
};



struct ListaAdyacencia{
	
	Node *dato;
	ListaAdyacencia *siguiente;
	
};
ListaAdyacencia *ini =NULL;
ListaAdyacencia *final =NULL ;


Grafo *crearGrafo(){
	
	Grafo *G;
	G = (Grafo*) malloc(sizeof(Grafo));
	G->inicio = NULL;
	return G;
	
}




/*
esEnteroValido
Entrada: char cadena
Salida: si es un numero entero o no

*/
int esEnteroValido(char cadena[100]) {
    int longitud = strlen(cadena);
    // Quitar espacios, saltos de línea, etcétera
    while (longitud > 0 && isspace(cadena[longitud - 1]))
        longitud--;
    if (longitud <= 0) return 0;
    int i;
    for (i = 0; i < longitud; ++i) {
        // En caso de que sea un guión, y que no esté al inicio, no es válido
        if (cadena[i] == '-' && i > 0) {
            return 0;
        }
        // Si no es dígito, tampoco es válido
        if (!isdigit(cadena[i]) && cadena[i] != '-') {
            return 0;
        }
    }
    return 1;
}






/*                      compararLineaConCedulaIndicador
    Compara una linea de texto con lo que se le pida comparar, esto 
    se hace por medio de un delimitador
---------------------------------------------------------------------*/

int compararLineaConCedulaIndicador(char bufer[1000],char cedula[1000],int indicador){
	int cont=0;
	char bufer2[1000],destino[1000];
	char delimitador[] = "^";
	strcpy( destino, bufer );
    char *token = strtok(destino, delimitador);
    if(token != NULL){
        while(token != NULL){
            if(cont == indicador){
            	strtok(token, "\n");
            	strcpy( bufer2, token );
            	if( strcmp(cedula, token) == 0){
            		return 1;
				}
			}
            cont++;
            token = strtok(NULL, delimitador);
        }
    }
    return 0;
}



/*                      validarNoexistenciaDeRuta
    Valida que la misma ruta no se registre en el archivo
---------------------------------------------------------------------*/
int validarNoexistenciaDeRuta(FILE *fp,char codigoCiberAtaque[100] ,char *fileName){
	char bufer[100];
	fp = fopen(fileName, "r");
    while (fgets(bufer, 100, fp)){
    	strtok(codigoCiberAtaque, "\n");
    	if(compararLineaConCedulaIndicador(bufer,codigoCiberAtaque,6) == 1 ){
    		return 1;
    		
		}
		
	}
	fclose(fp);
	return 0;
}


int pasarDeArbolAListaPais(ArbolPaises* node,Lista *L){
	char buffer2[1000];
	if (node != NULL) {
		pasarDeArbolAListaPais(node->left,L);

		insertarDato(L, node->nombre);
		
        pasarDeArbolAListaPais(node->right,L); 
        
    }
}



int buscarPaisExiste(char pais[1000]){
	Nodo *i;
	Lista* L;
	L=listaNueva();
	pasarDeArbolAListaPais(raiz,L);
	
	for(i=L->inicio;i != NULL; i=i->siguiente){
		
		if(strcmp(i->dato,pais) == 0){
			liberarLista(L);
			return 1;
		}
			
	}
	liberarLista(L);
	return 0;
	
}


int vaidarDelincuenteTipo(int delincuente,char tipoAtaque[1000]){
	int cont=0;
	ListaCiberdelincuente* aux = primerCiberdelincuente;
	TipoCiberataque* aux2 = primerTipo;
	while (aux != NULL){
	    	 
	    if(delincuente == aux->id ){
	    	
	    	cont++;	
		}
	    aux = aux->siguiente;   
	}
	
	
	while (aux2 != NULL){
	   			
		if(strcmp(tipoAtaque,aux2->nombreAtaque) == 0){
			
			cont++;
					
		}
		aux2 = aux2->siguiente;     
	}
	return cont;

}



int pedirRuta(char codigoCiberAtaque[100]){
	
	char tipo[100],cantidadDatos[100],tiempo[100],ruta[100], delincuente[100],origen[100],fin[100];
	
	int aux;
	
	char *filename = "Registro de ciberataques.txt";
	char espacio[]="\n";
	FILE *fp, *fx;
    // open the file for writing
	
    
    // write to the text file
    
	int numeroEntero;
    
    while(1){
    	printf("\nIndique el nombre del lugar: ");
    	gets(origen);
    	printf("\nIndique el nombre del lugar de destino: ");
    	gets(fin);
		printf("Ingrese la cantidad de datos comprometidos -> ");
		gets(cantidadDatos);
		printf("Ingrese el tiempo del lugar a el destino -> ");
		gets(tiempo);
	    printf("Ingrese el nombre del tipo de ciberataque -> ");
		gets(tipo);
		printf("Ingrese el codigo del delincuente -> ");
		gets(delincuente);
		
	    numeroEntero=strtol(delincuente, NULL, 10);
		if( !esEnteroValido(tiempo) || !esEnteroValido(cantidadDatos) ||buscarPaisExiste(origen) == 0 ||buscarPaisExiste(fin) == 0 ||vaidarDelincuenteTipo(numeroEntero,tipo) != 2 ) 
		{
			printf("\n\nAlguno de los datos dados no cumplen el formato solicitado, intente de nuevo \n\n");
			
		} 
		else{
			break;
		}
	}

	while(1){
			if(validarNoexistenciaDeRuta(fp,codigoCiberAtaque,filename) == 0){
			fp = fopen(filename, "a");
	
		    if (fp == NULL)
		    {
		        printf("Error abriendo:  %s", filename);
		        return;
		    }
		    
			fprintf(fp,  "%s^%s^%s^%s^%s^%s^%s^N\n",origen,fin,tiempo,delincuente,cantidadDatos,tipo,codigoCiberAtaque);
			printf("\nSe registro con exito\n");
			fclose(fp);
			break;
		}
	    else{
	    	printf("\nCiberataque ya existe\n\n ");
	    	printf("\nIndique el codigo de ciberataque: ");
    		gets(origen);
		}
	}
	

    // close the file
    return 0;
	
}

void insertarVertices(char nombre[100],Grafo *G)
{	
	
	int i;
	Node *aux;
	Node *nuevo = (Node*)malloc(sizeof(Node));
	fflush(stdin);
	for(i=0;i<100;i++){
		nuevo->dato[i]=nombre[i];
		
	}
	
	nuevo->siguiente = NULL;
	nuevo->adyacencia = NULL;
	nuevo->visitado = 0;
	nuevo->terminado = 0;
	nuevo->monto = -1;
	strcmp(nuevo->anterior,"NULL");
	nuevo->anterior[0] = 0;
	
	if(G->inicio == NULL)
	{
		G->inicio = nuevo;
	}
	else
	{
		aux = G->inicio;
		while(aux->siguiente != NULL)
		{
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}
}

void ponerPaisEnLista(ArbolPaises* node, Lista *L, char pais[1000]){
    if (node != NULL) {
        ponerPaisEnLista(node->left,L,pais);
        if(strcmp(node->nombre,pais) == 0){
        	
        	insertarDato(L, pais);
		}
        
        ponerPaisEnLista(node->right,L,pais);
    }
}

void paisesALista(ArbolPaises* node, Lista *L, char pais[1000]){
    if (node != NULL) {
        paisesALista(node->left,L,pais);
        if(strcmp(node->nombre,pais) != 0){
        	insertarDato(L, node->nombre);
		}
        
        paisesALista(node->right,L,pais);
    }
}


void crearVertices(ArbolPaises* node,Grafo *G,char pais[1000]){
	
	Lista *L;
	L=listaNueva();
	Nodo *i;
	
	ponerPaisEnLista(raiz, L, pais);
	paisesALista(raiz, L, pais);
	for(i=L->inicio; i!=NULL; i=i->siguiente){
		insertarVertices(i->dato,G);
	}
	liberarLista(L);
}




void agregarArista(Node *aux, Node *aux2, Arista *nuevo)
{
	Arista *a;
	if(aux->adyacencia == NULL)
	{
		aux->adyacencia = nuevo;
		nuevo->vertice = aux2;
	}
	else
	{
		a = aux->adyacencia;
		while(a->siguente != NULL)
		{
			a = a->siguente;
		}
		nuevo->vertice = aux2;
		a->siguente = nuevo;
	}
}


/*                      insertarArista
    Agrega arista entre los nodos 
---------------------------------------------------------------------*/
void insertarArista(char origen[100],char destino[100],int peso,Grafo *G)
{

	Arista *nuevo = (Arista*)malloc(sizeof(Arista));
	Node *aux, *aux2;
	nuevo->siguente = NULL;
	
	if(G->inicio == NULL)
	{
		printf("El grafo esta vacio");
		return;
	}
	
	
	aux = G->inicio;
	aux2 = G->inicio;
	
	while(aux2 != NULL)
	{
		
		if(strcmp(aux2->dato,destino) == 0)
		{	
			break;
		}
		aux2 = aux2->siguiente;
		
	}
	
	while(aux != NULL)
	{
		if(strcmp(aux->dato,origen) == 0)
		{	
			agregarArista(aux, aux2, nuevo);
			
			return;
		}
		aux =  aux->siguiente;
	}
	
}


/*                      crearRutasGrafo
    Permite el filtro de las rutas segun lo que quiera el usuario
---------------------------------------------------------------------*/
void crearRutasGrafo(Grafo *G){
	char bufer[1000],destino[1000],lugarOrigen[1000],lugarDestino[1000],tipo[100],opcion[100],codigo[100];
	char delimitador[] = "^";
	int peso,cont=0,aux;
	FILE *fp;
	
	
	fp=fopen("Registro de ciberataques.txt","r");
	char *token;
	
	
	while (fgets(bufer, 1000, fp)){
    	
    	strtok(bufer, "\n");
		strcpy( destino, bufer );
	    token = strtok(destino, delimitador);
	    
	    if(token != NULL){
	        while(token != NULL){
	        	if(cont == 6){
	        		strcpy( codigo, token );
				}
	        	if(cont == 0){
	            	
	            	strcpy( lugarOrigen, token );
				}
				if(cont == 1){
	            	
	            	strcpy( lugarDestino, token );
				}
	            if(cont == 2){
	            	
	            	peso= strtol(token, NULL, 10);
				}
	            cont++;
	            token = strtok(NULL, delimitador);
	        }
	    }
		cont=0;
		
		insertarArista(lugarOrigen,lugarDestino,peso,G);	
				
	}
	fclose(fp);
}

/*                      visualizarGrafo
    Permite ver el grafo y como se relazionan los nodos entre si
---------------------------------------------------------------------*/
void visualizarGrafo(Grafo *G)
{	
	
    Node *aux = G->inicio;
    Arista *ar;
    printf("\nNodes \n");
    
    while(aux != NULL)
	{   
	    printf("%s:    ", aux->dato);
        if(aux->adyacencia != NULL)
		{
            ar = aux->adyacencia;
            while(ar != NULL)
			{ 
			    printf(" %s", ar->vertice->dato);
                ar = ar->siguente;
            }
        }
        printf("\n");
        aux = aux->siguiente;
    }
    printf("\n");
}



void MostrarCiberataques(){
	FILE *fp;
	
	char bufer[1000],destino[1000],lugarOrigen[1000],lugarDestino[1000],tipo[100],opcion[100],codigo[100];
	char delimitador[] = "^";
	fp=fopen("Registro de ciberataques.txt","r");
	char *token;
	int cont;
	printf("\nCiberataques:");
	while (fgets(bufer, 1000, fp)){
    	
    	strtok(bufer, "\n");
		strcpy( destino, bufer );
	    token = strtok(destino, delimitador);
	    
	    if(token != NULL){
	        while(token != NULL){
	        	if(cont == 6){
	        		printf("\nCodigo Ciberataque: %s",token);
				}
	        	if(cont == 0){
	            	
	            	printf("\n------------\nOrigen: %s",token);
				}
				if(cont == 1){
	            	
	            	printf("\nDestino: %s",token);
				}
	            if(cont == 2){
	            	
	            	printf("\nTiempo: %s",token);
				}
				if(cont == 3){
	            	
	            	printf("\nDelincuente: %s",token);
				}
				if(cont == 4){
	            	
	            	printf("\nCantidad de datos comprometidos: %s",token);
				}
				if(cont == 5){
	            	
	            	printf("\nTipo: %s",token);
				}
				if(cont == 7){
					strtok(token, "\n");
	            	if(compararLineaConCedulaIndicador(bufer,"N",7)){
	            		printf("\nNo fue una simulacion\n");
					}
					else{
						printf("\nFue una simulacion\n----------------\n");
					}
	            	
				}
	            cont++;
	            token = strtok(NULL, delimitador);
	        }
	    }
		cont=0;	
				
	}
	fclose(fp);
	
}



/*                      eliminarRuta
    Elimina del txt la ruta que se pida eliminar
---------------------------------------------------------------------*/
int eliminarRuta(){
	
	char bufer[1000],ciberataque[1000];         // Aquí vamos a ir almacenando cada línea
    FILE *fp;
    printf("\nIngrese el codigo del ciberataque: ");
    gets(ciberataque);
	
    Nodo *i;
    Lista *L;
    L = listaNueva();
    fp = fopen("Registro de ciberataques.txt", "r");
    
    while (fgets(bufer, 1000, fp)){
    	
    	if(compararLineaConCedulaIndicador(bufer,ciberataque,6) == 0 ){
    		
    		insertarDato(L,bufer);
    
    		printf(" ");
		}
		else{
			printf("\nSe elimino ciberataque\n");
		}	
	}
	printf("\n ");
	fclose(fp);
	fp = fopen("Registro de ciberataques.txt", "w");
	
	for(i=L->inicio;i != NULL;i=i->siguiente){
		
		fprintf(fp,"%s",i->dato);	
	}

	fclose(fp);
	liberarLista(L);
}


/*                      buscarDatoEnTxt
    Busca en el archivo la existencia de lo que se le pida, esta hecha 
    de una manera que permita revisar cualquier archivo siempre y 
    cuando sea el mismo delimitador
---------------------------------------------------------------------*/

int buscarDatoEnTxt(FILE *fp,char cedula[100],char *fileName,int indicador){
	char bufer[100];
	fp = fopen(fileName, "r");
    while (fgets(bufer, 100, fp)){
    	strtok(cedula, "\n");
    	if(compararLineaConCedulaIndicador(bufer,cedula,indicador) == 1 ){
    		return 1;
    		
		}
		
	}
	fclose(fp);
	return 0;
}



/*                      modificarRuta
    Modifica del txt la ruta que se pida modificar
---------------------------------------------------------------------*/

int modificarRuta(){
	
	char bufer[1000],ciberataques[1000];         // Aquí vamos a ir almacenando cada línea
    FILE *fp;
    printf("\nIngrese el codigo de ciberataque: ");
    gets(ciberataques);
    if(buscarDatoEnTxt(fp,ciberataques,"Registro de ciberataques.txt",6) == 0){
    	printf("\nNo se en cuentra registrado el ciberataque\n");
    	return 0;
	}
    
    Nodo *i;
    Lista *L;
    L = listaNueva();
    fp = fopen("Registro de ciberataques.txt", "r");
    while (fgets(bufer, 1000, fp)){
    	
    	if(compararLineaConCedulaIndicador(bufer,ciberataques,6) == 0  ){
    		
    		insertarDato(L,bufer);
    		printf(" ");
		}		
	}
	printf("\n ");
	fclose(fp);
	fp = fopen("Registro de ciberataques.txt", "w");
	for(i=L->inicio;i != NULL;i=i->siguiente){
		strtok(i->dato, "\n");
		fprintf(fp,"%s\n",i->dato);	
	}
	fclose(fp);
	pedirRuta(ciberataques);
	liberarLista(L);
	printf("Se modifico\n");
}


/*                      eliminarRutaVinculadasAPais
    Elimina del txt la ruta que se pida eliminar
---------------------------------------------------------------------*/
int eliminarRutaVinculadasAPais(){
	
	char bufer[1000],pais[1000];         // Aquí vamos a ir almacenando cada línea
    FILE *fp;
    printf("\nIngrese el pais: ");
    gets(pais);
	
    Nodo *i;
    Lista *L;
    L = listaNueva();
    fp = fopen("Registro de ciberataques.txt", "r");
    
    while (fgets(bufer, 1000, fp)){
    	
    	if(compararLineaConCedulaIndicador(bufer,pais,0) == 0 && compararLineaConCedulaIndicador(bufer,pais,1) == 0){
    		
    		insertarDato(L,bufer);
    
    		printf(" ");
		}
		else{
			printf("\nSe elimino ciberataque\n");
		}	
	}
	printf("\n ");
	fclose(fp);
	fp = fopen("Registro de ciberataques.txt", "w");
	
	for(i=L->inicio;i != NULL;i=i->siguiente){
		
		fprintf(fp,"%s",i->dato);	
	}

	fclose(fp);
	liberarLista(L);
}



void menuCiberAtaque(){
	
	 printf("|================Ciberataques==================|\n");
    printf("\t1. Insertar\n");
    printf("\t2. Modificar\n");
    printf("\t3. Eliminar\n");
    printf("\t4. Eliminar ciberataques vinculados a un pais\n");
    printf("\t5. Mostrar ciberataques\n");
    printf("\t6. Atras\n");
	Grafo *G;
	G=crearGrafo();
	
	char origen[100],destino[100], opcion[100],codigoCiberAtaque[100];
	int numeroEntero;
	
	printf("Digite su opcion: ");
    gets(opcion);
	numeroEntero = strtol(opcion, NULL, 10);
	if(numeroEntero == 1){
		
		printf("Ingrese el codigo del ciberataque -> ");
		gets(codigoCiberAtaque);
		pedirRuta(codigoCiberAtaque);
	}
	else{
		if(numeroEntero == 2){
			modificarRuta();
		}
		else{
			if(numeroEntero == 3){
				eliminarRuta();
			}
			else{
				if(numeroEntero == 4){
					eliminarRutaVinculadasAPais();	
				}
				else{
					if(numeroEntero == 5){
						MostrarCiberataques();
					}
				}
				
			}
		}
				
	}
	
}


int pasarDeArbolALista(ArbolPaises* node,Lista *L){
	char numero[100];
	char buffer2[1000];
	if (node != NULL) {
		pasarDeArbolALista(node->left,L);
		sprintf(numero, "%d", node->codigo);
		strcat(strcpy(buffer2, numero), "^");
		strcat(strcpy(buffer2, buffer2), node->nombre);
		insertarDato(L, buffer2);
        pasarDeArbolALista(node->right,L); 
        
    }
}

int revisarLista(int numeroPais,Lista *L){
	Nodo *i;
	FILE *fp;
	int cont=0, aux=0;
	char bufer[1000],bufer2[1000],destino[1000];
	char delimitador[] = "^";
    char *token;
    sprintf(bufer, "%d", numeroPais);
	for(i=L->inicio;i != NULL; i=i->siguiente){
		strcpy( destino, i->dato );
		token = strtok(destino, delimitador);
    	if(token != NULL){
        while(token != NULL){
            if(cont == 0){
            	strcpy( bufer2, token );
            	
            	if( strcmp(bufer, token) == 0){
            		aux=1;
				}
			}
			else{
				if(aux == 1){
					fp=fopen("Registro de ciberataques.txt","a");
					fprintf(fp,"%s^",token);
					
					fclose(fp);
					return 1;
				}
			}
            cont++;
            token = strtok(NULL, delimitador);
        }
        cont=0;
    	}	
	}
	return 0;
	
}


/*                      eliminarSimulaciones
    Elimina del txt la ruta que se pida eliminar
---------------------------------------------------------------------*/
int eliminarSimulaciones(){
	
	char bufer[1000];         // Aquí vamos a ir almacenando cada línea
    char letra[1000]={"S"};
	FILE *fp;
	
    Nodo *i;
    Lista *L;
    L = listaNueva();
    fp = fopen("Registro de ciberataques.txt", "r");
    
    while (fgets(bufer, 1000, fp)){
    	
    	if(compararLineaConCedulaIndicador(bufer,letra,7) == 0 ){
    		
    		insertarDato(L,bufer);
    
    		printf(" ");
		}
		else{
			printf("\nSe elimino simulacion\n");
		}	
	}
	printf("\n ");
	fclose(fp);
	fp = fopen("Registro de ciberataques.txt", "w");
	
	for(i=L->inicio;i != NULL;i=i->siguiente){
		
		fprintf(fp,"%s",i->dato);	
	}

	fclose(fp);
	liberarLista(L);
}




void simulacionCiberAtaques(int H){
	FILE *fx;
	Lista *L;
    
	int i,numeroDelinceunte,tiempo,datos,numeroPais,tipo,valor=1;
	ListaCiberdelincuente* aux = primerCiberdelincuente; 
	int prueba=0;
	srand(time(NULL));
	while( prueba < H){
		L = listaNueva();
		while(1){
		numeroDelinceunte= rand() % 1000;
		valor=1;
	    while (aux != NULL){
	    	 
	    	
	        if(numeroDelinceunte == aux->id){
	    		valor=0;
	        	break;
			}
	        aux = aux->siguiente;   
	    }
	    if(valor == 0){
	    	break;
		}
	    aux = primerCiberdelincuente;    
		}
		valor=1;
		    
		int contador=0; 
		pasarDeArbolALista(raiz,L);  
		
		
		while(contador<2){
			numeroPais = rand() %  1000;
			
			if(revisarLista(numeroPais, L) == 1){
				contador++;
			}
			
		}  
		tiempo= rand() % 1000;
		datos= rand() % 1000;
		
		fx=fopen("Registro de ciberataques.txt","a");
		fprintf(fx,"%d^%d^%d^",tiempo,numeroDelinceunte,datos);
		tiempo=0;
		datos=0;
		
	   	while(1){
	   		TipoCiberataque* aux2 = primerTipo;
	   		tipo= rand() % 1000;
	   		while (aux2 != NULL){
	   			
				if(tipo == aux2->codigoAtaque){
					fprintf(fx,"%s^",aux2->nombreAtaque);
					
					valor=0;
					
				}
		        aux2 = aux2->siguiente;     
		    }
		    
		    if(valor == 0){
		    	break;
			}
		}
	    
		//Genera letras al azar  
	    
	    fprintf(fx,"%c",'A' + rand() % (('Z' - 'A') + 1));
	    fprintf(fx,"%c",'A' + rand() % (('Z' - 'A') + 1));
	    fprintf(fx,"%c^S\n",'A' + rand() % (('Z' - 'A') + 1));
	    fclose(fx);	
	    liberarLista(L);
	    prueba++;
	}
	
	printf("Simulacion Exitosa\n");
	MostrarCiberataques();
	char opcion[1000];
	int numeroEntero;
	while(1){
		printf("Desea eliminar las simulaciones (Si= 1 y No=0)?\n");
		gets(opcion);
		numeroEntero = strtol(opcion, NULL, 10);
		if(numeroEntero == 1){
			eliminarSimulaciones();
			break;
		}
		else{
			if(numeroEntero == 0){
				break;
			}
		}	
	}
	
	
}



/*                      insertarPila
    
---------------------------------------------------------------------*/
void insertarPila(Node* aux)
{
	ListaAdyacencia *nuevo = (ListaAdyacencia*)malloc(sizeof(ListaAdyacencia));
	nuevo->dato = aux;
	nuevo->siguiente = NULL;
	if(ini == NULL)
	{
		ini = nuevo;
		final = nuevo;
	}
	else
	{
	   nuevo->siguiente = ini;
	   ini = nuevo;    	
	}
}

/*                      imprimirCodigo
    Imprime el codigo del lugar 
---------------------------------------------------------------------*/
void imprimirCodigo(char lugar[100]){
	FILE *fp;
	char bufer[100];
	int cont=0;
	char bufer2[1000],destino[1000];
	char delimitador[] = "^";
	char *token;
	fp = fopen("Registro de lugares viaje.txt", "r");
    while (fgets(bufer, 100, fp)){
    	strtok(bufer, "\n");
    	if(compararLineaConCedulaIndicador(bufer,lugar,0) == 1 ){
			strcpy( destino, bufer );
		    token = strtok(destino, delimitador);
		    if(token != NULL){
		        while(token != NULL){
		            if(cont == 6){
		            	strcpy( bufer2, token );
		            	printf("%s,",bufer2);
					}
		            cont++;
		            token = strtok(NULL, delimitador);
		        }
		    }
    		
		}
		
	}
	fclose(fp);
	
}

/*                      desencolar
    
---------------------------------------------------------------------*/

Node*desencolar()
{
	ListaAdyacencia *aux;
	if(ini == NULL)
	{
		return NULL;
	}
	else
	{
		aux = ini;
		ini = ini->siguiente;
		aux->siguiente = NULL;
		
		if(ini == NULL)
		{
			final = NULL;
		}
	}
	Node*resultado = aux->dato;
	imprimirCodigo(aux->dato->dato);
	free(aux);
	return resultado;
}
/*                      reiniciar
    
---------------------------------------------------------------------*/
void reiniciar(Grafo *G)
{
	if(G->inicio != NULL)
	{
		Node *aux = G->inicio;
		while(aux != NULL)
		{
			aux->visitado = aux->terminado=0;
		    aux = aux->siguiente;
		}
	}
}











/*                      dijkstra
    Imprime los lugares segun la ruta mas corta de la casa del jefe
    al otro punto o lugar
---------------------------------------------------------------------*/

void dijkstra(Grafo *G)
{
	FILE *fp;
	Node *aux = G->inicio;
	char a[100],b[100];
	printf("Ingresar Pais final-> ");
	gets(b);
	
	if(buscarPaisExiste(b) == 0 || strcmp(aux->dato,b) == 0){
    	printf("\nError (No se encuentra registrado el lugar o se puso el mismo lugar de origen con el de destino)\n");
    	return ;
	}
	
	strcpy(a,aux->dato);
	while(aux != NULL)
	{
		if(strcmp(aux->dato,a) == 0)
		{
			aux->terminado = 1;
			aux->monto = 0;
			break;
		}
		aux = aux->siguiente;
	}
	
	if(aux == NULL)
	{
		printf("Vertice no encontrado \n");
		return;
	}
	
	int cont=0;
	while(aux != NULL)
	{
		
		Arista *a = aux->adyacencia;
		while(a != NULL)
		{
			if(a->vertice->monto == -1 || aux->monto + a->peso < a->vertice->monto)
			{
				
				a->vertice->monto = aux->monto + a->peso;
				for(cont=0;cont<100;cont++){
					a->vertice->anterior[cont] = aux->dato[cont];	
				}
				
			}
			a = a->siguente;
		}
		
		aux = G->inicio;
		Node *min = G->inicio;
		while(min->anterior[0] == 0 || min->terminado == 1)
		{
			min = min->siguiente;
		}
		
		while(aux != NULL)
		{
			if(aux->monto < min->monto && aux->terminado == 0 && aux->anterior[0] != 0)
			{
				min = aux;
				
			}
			aux = aux->siguiente;
		}
		
		aux = min;
		aux->terminado = 1;
		
		if(strcmp(aux->dato,b) == 0 )
		{
			break;
		}
			
	}
	char temp[100];
	while(aux->anterior[0] !=  0)
	{
		
		insertarPila(aux);
		strcpy(temp,aux->anterior);
		
		aux = G->inicio;
		
		while(strcmp(aux->dato,temp) != 0 && aux->dato != NULL )
		{
			
			aux = aux->siguiente;
			
		}
	
	}
	char cadena[100],auxCadena[100];
	insertarPila(aux);
	while(ini != NULL)
	{

		printf("%s-------->    ", desencolar()->dato);
		
	}
	printf("\n");
	reiniciar(G);
	
	
}







/*                      insertarNodosEnLista
    Mete los nombres de los lugares en la lista
---------------------------------------------------------------------*/
int buscarEnAdyacencia(Grafo *G,char nombre[100]){
	Node *aux;
	Arista *ar;
	for(aux=G->inicio;aux != NULL; aux=aux->siguiente){
		for(ar=aux->adyacencia;ar !=NULL; ar=ar->siguente){

			if(strcmp(ar->vertice->dato,nombre) == 0){
				return 0;
			}
		}	
	}
	return 1;
}
/*                      validarTodosLosLugaresRutas
    Se asegura que todos los lugares tengan un referente que los conecte
    con el resto del grafo
---------------------------------------------------------------------*/
int validarTodosLosLugaresRutas(Grafo *G){
	Lista *L;
	L=listaNueva();
	Node *aux;
	Arista *ar;
	Nodo *auxLista;
	for(aux=G->inicio->siguiente;aux != NULL; aux=aux->siguiente){
		
		if(buscarEnAdyacencia(G,aux->dato) == 1){
			return 1;
		}		
	}
	return 0;

}


/*          FUNCION PARA BORRAR TODAS LAS ARISTAS DE UN NODO
    esta funcion es utilizada al borrar un nodo pues si tiene aristas
    es nesesario borrarlas tambien y dejar libre la memoria
---------------------------------------------------------------------*/
void vaciar_aristas(Node *aux)
{	
	
    Node *q,*r;
    q=aux->adyacencia->vertice;
    
    while(aux->adyacencia->siguente != NULL)
    {	
    	
        r=q;
        
        q->adyacencia=q->adyacencia->siguente;
        
        free(r);
    }
}
/*                      ELIMINAR NODO
    funcion utilizada para eliminar un nodo del grafo
    pero para eso tambien tiene que eliminar sus aristas por lo cual
    llama a la funcion vaciar_aristas para borrarlas
---------------------------------------------------------------------*/
void eliminar_nodo(char *var,Grafo *G)
{   

    Node *aux,*ant;
    aux=G->inicio;
    
    if(aux==NULL)
     {
         printf("Grafo vacio\n");
         return;
     }

    while(aux!=NULL)
    {
    	
        if(strcmp(aux->dato,var)==0)
        {
        	
            if(aux->adyacencia!= NULL){//Ver
            	
                vaciar_aristas(aux);
			}
            if(aux==G->inicio)
            {

                    G->inicio=G->inicio->siguiente;
                    free(aux);
                    
                    return;
                    
            }
            else
            {
                ant->siguiente = aux->siguiente;
                free(aux);
                 
                return;
            }
        }
        else
        {
            ant=aux;
            aux=aux->siguiente;
         }
        
    }

}


/*                      eliminar_arista
    Elimina la arista entre dos nodos
---------------------------------------------------------------------*/

void eliminar_arista(char *ini,char *fin,Grafo *G)
{
	 
    Node *aux, *aux2;
    Arista *r,*q;
    aux=G->inicio;
    aux2=G->inicio;
    
    while(aux2!=NULL)
    {
        if(aux2->dato==fin)
        {
            break;
        }
        else
        aux2=aux2->siguiente;
    }
    
     while(aux!=NULL)
    {
    	
        if(strcmp(aux->dato,ini)==0)
        {	
        	
            q=aux->adyacencia;
            while(q != NULL)
            {
            	
                if(q->vertice == aux2)
                printf("");
                {
                	
                    if(q->vertice == aux->adyacencia->vertice)
                        aux->adyacencia=aux->adyacencia->siguente;
                    else
                        r->siguente=q->siguente;
                    free(q);
                    
                    return;
                }
                q=q->siguente;
            }
            r=q;
            
        }
        aux = aux->siguiente;
    }
}



/*                      limpiarGrafo
    Limpia el grafo para que la proxima vez no se creen los mismo nodos
---------------------------------------------------------------------*/
void limpiarGrafo(Grafo *G)
{	
	int cont=0;
    Node *aux = G->inicio;
    Arista *ar;
    
    while(aux != NULL)
	{   
		
		while(aux->adyacencia != NULL){
			eliminar_arista(aux->dato,aux->adyacencia->vertice->dato,G);
			cont++;
			
		}
        aux = aux->siguiente;  
        cont=0;
    }
    
    
    aux = G->inicio;
    while(aux != NULL)
	{   
		
        eliminar_nodo(aux->dato,G);
        
        aux = aux->siguiente;
        
    }
    
}

/*                      validarQueTodosLLevenAOtro
    Ve que todos los vertices lleven a otro
---------------------------------------------------------------------*/
int validarQueTodosLLevenAOtro(Grafo *G){
	Arista *ar;
	int cont=0;
	Node *aux;
	for(aux=G->inicio; aux != NULL; aux=aux->siguiente){
		if(aux->adyacencia == NULL){
			return 0;
		}
	}
	return 1;
	
}

int revisarQueRutaSiLLeveAPais(char bufer[1000]){
	
	int cont=0,valor=0;
	char bufer2[1000],destino[1000];
	char delimitador[] = "^";
	strcpy( destino, bufer );
    char *token = strtok(destino, delimitador);
    	
    if(token != NULL){
	    while(token != NULL){
	        if(cont == 0){
	            	
	            if (buscarPaisExiste(token)== 1){
	            	printf("(%s y ",token);
	            	valor++;
				}
	            	
			}
			if(cont == 1){
					
	        	if (buscarPaisExiste(token)== 1){
	            	printf("%s)\n ",token);
	            	valor++;
				}   	
			}
	        cont++;
	        token = strtok(NULL, delimitador);
	        }
    	}
		cont=0;	

    if(valor == 2){
	    return 1;
	}
    return 0;
	
}

int validarRutasYaPaises(){
	
	
	int cont=0,valor=0;
    
    char bufer[1000];         // Aquí vamos a ir almacenando cada línea
	FILE *fp;
	
    fp = fopen("Registro de ciberataques.txt", "r");
    
    while (fgets(bufer, 1000, fp)){
    	if(revisarQueRutaSiLLeveAPais(bufer) == 0){
    		fclose(fp);
    		return 0;
		}
	}
	fclose(fp);
    return 1;
	
}


//main
int main(void){
    //PRECARGA DE DATOS (solo voy a meter un registro por cada uno para que ustedes metan sus propios datos)
    //si es posible cambien los datos y carguen unos que sean mas utiles
    char* channels[] = {"channel 1" , "channel 2" , "channel 3"};
    
    insertarTipoCiberAtaque(1, "tipo1" , "atack troyano" , channels);
	char opcion[100];
	char pais[1000];
    char* atacks[] = {"atack 1" , "atack 2" , "atack 3"};//procuren que siempre sean 3 ataques
    insertarCiberdelinciente(1, "n/a", "costa rica", atacks);

    insertarHoja(raiz, 506, "Costa Rica" , 5094000, "America");
    insertarHoja(raiz, 974, "Qatar" , 2881000, "Asia");
    insertarHoja(raiz, 55, "Brasil" , 2126000, "America");
    insertarHoja(raiz, 358, "Finlandia" , 200000, "Europa");
    insertarHoja(raiz, 96, "Venezuela" , 5531000, "America");
    insertarHoja(raiz, 63, "Filipinas" , 1096000, "Oceania");
    int option = 0,cantidad;
    char cantidadAux[100];
    
    Grafo *G;
	G=crearGrafo();
    
    
    
    while (option != 9){
        menuPrincipal();
        printf("Digite su opcion: ");
        gets(opcion);
        option = strtol(opcion, NULL, 10);
        //eleccion de tipos de ciberataques
        
        if(option == 1){
            int option2 = 0;
            while (option2 != 5){
                menu1();
                printf("Digite su opcion: ");
                scanf("%d", &option2);
                if (option2 == 1){
                    modificarTipoCiberataque();
                }
                //como les dije, esto no se puede implementar ya que se necesita de los grafos
                else if (option2 == 2){
                    printf("Por implementar\n");
                }
                
                else if (option2 == 3){
                    mostrarTiposDeCiberataques();
                }
                else if(option2 == 4){
                    break;
                }
                else{
                    printf("Error: Opcion no valida!");
                }
            }   
        }
        //eleccion de ciberdelincuentes
        else if(option == 2){
            int option2 = 0;
            while (option2 != 5){
                menu2();
                printf("Digite su opcion: ");
                scanf("%d", &option2);
                if (option2 == 1){
                    modificarCiberdelincuente();
                }
                else if (option2 == 2){
                    //como les dije, esto no se puede hacer porque va mas alla de los registros
                    printf("Por implementar");
                }
                else if (option2 == 3){
                    consultarCiberdelincuentes();
                }
                else if(option2 == 4){
                    break;
                }
                else{
                    printf("Error: Opcion no valida!");
                }
            }
        }
        //Opciones paises
        else if(option == 3){
            int option2 = 0;
            while (option2 != 6){
                menu3();
                printf("Digite su opcion: ");
                scanf("%d", &option2);
                if (option2 == 1){
                    int codigo;
                    int habitantes;
                    char nombre[25];
                    char continente[25];
                    printf("Ingrese el codigo del pais: ");
                    scanf("%d", &codigo);
                    printf("Ingrese el nombre del pais: ");
                    scanf("%s", &nombre);
                    printf("Ingrese la cantidad de habitantes del pais: ");
                    scanf("%d", &habitantes);
                    printf("Ingrese el continente al que pertenece el pais: ");
                    scanf("%s", &continente);
                    insertarHoja(raiz, codigo, nombre, habitantes, continente);
                }
                else if (option2 == 2){
                    int codigo;
                    printf("Ingrese el codigo del pais: ");
                    scanf("%d", &codigo);
                    modificarPais(raiz, codigo);
                }
                
                else if (option2 == 3){
                    int codigo;
                    printf("Ingrese el codigo del pais: ");
                    scanf("%d", &codigo);
                    eliminarHoja(raiz, codigo);
                }
                else if(option2 == 4){
                    inorden(raiz);
                    getchar();
                    getchar();
                }
                else if(option2 == 5){
                    jerarquia(raiz, 1, 2);
                    getchar();
                    getchar();
                }
                else if(option2 == 6){
                    break;
                }
                else{
                    printf("Error: Opcion no valida!");
                }
            
            }
        }
        else if(option == 4){
        	
        	menuCiberAtaque();
		}
		else if(option == 6){
			printf("Digite la cantidad de simulaciones que desea hacer: ");
            gets(cantidadAux);
            cantidad = strtol(cantidadAux, NULL, 10);    
            simulacionCiberAtaques(cantidad);
            	
		}
		else if(option == 7){
			
			
			if(validarRutasYaPaises() == 1){
				printf("Indique el pais origen:");
				gets(pais);
				if(buscarPaisExiste(pais) != 0){
					crearVertices(raiz,G,pais);
					crearRutasGrafo(G);
					printf("Resumen de grafo:\n");
					visualizarGrafo(G);
				    if(validarTodosLosLugaresRutas(G) == 0 && validarQueTodosLLevenAOtro(G) == 1){
						printf("\n\n********Simulacion de ruta mas corta al destino********\n\n");
						dijkstra(G);
					}
					else{
						printf("\n\nTodos los lugares deben tener una ruta por la cual llegar.\n\nIntente de nuevo\n\n");
					}
											
					limpiarGrafo(G);
				}
				else{
					printf("\n\nNo se encuentra el pais seleccionado.\n\nIntente de nuevo\n\n");	
				}
			}
			else{
				printf("\n\nExisten rutas que llevan a lugares no registrados.\n\nIntente de nuevo\n\n");
			}	    
			
		}
    }
    return 0;
}
