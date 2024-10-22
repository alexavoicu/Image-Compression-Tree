Rezolvarea consta in mai multe etape:
1. Interpretarea argumentelor primite in libnia de comanda, tratand cele 3 tipuri de cerinte. Am retinut numarul cerintei in variabila option, iar utilizand atoi, am extras factorul de compresie, si fisierele de in si out, iar in functie de tipul cerintei am deschis fisierul de in in mod corespunzator(ca binar sau text).
2. Citirea din fisierul de input a dimensiunii si a valorilor rgb din imagine. Pentru a face asta am utilizat functiile fscanf(pentru dimensiune) si fread(pentru citirea imaginii). Am citit aceste valori sub forma unui vector de unsigned char alocat dinamic, pentru a facilita popularea matricii pe care am utilizat o pentru a retine informatiile din imagine. Am parcurs vectorul pozitie cu pozitie (cate 3 pozitii odata deoarece sunt 3 culori), pentru a extrage informatiile si a le plasa in matricea mea de structuri de tip pixel (ce contine cate un camp de unsigned char pentru fiecare culoare) alocata dinamic. Am inchis fisierul fin.
3. Am apelat functia ce imi creeaza arborele cuaternar de compresie cu imaginea, pozitia de start (0,0), dimensiunea initiala (dim pozei), factorul si adresa dimensiunii laturii celei mai mari zonă din imagine care a rămas nedivizata. In cadrul acestei functii aloc dinamic nodul pe care urmeaza sa-l inserez si calculez "mean-ul" dupa formulele scrise in cerinta. Apoi verific daca mean este mai mic decat factorul primit ca argument, iar in caz afirmativ creez un nod frunza. Altfel creez un nod intern si apelez functia create_tree pentru cele 4 zone in care se divizeaza matricea.
4. In cazul in care cerinta rezolvata este 1, cu ajutorul functiilor get_tree_depth si get_num_leaves aflu adancimea si numarul de frunze. Functia get_num_leaves este o functie recursiva care parcurge arborele, in cazul in care nodul este NULL returneaza 0 , iar la frunza 1. Dupa care se apeleaza pentru toti cei 4 copii ai nodului primit ca parametru, iar in final aduna rezultatul celor 4 apeluri. Functia de depth functioneaza pe acelasi principiu, doar ca in loc de suma, apeleaza o functie de maxim pentru cele 4 rezultate. Apoi le scriu in fout, alaturi de max_leaf_size(parametrul din functia de create tree).
Daca optiunea este 2, se scrie in fisierul binar dimensiunea si apoi se apeleaza functia de afisare pe nivel, care este preluata din curs si adaptata pentru un arbore cuaternar.
La final se elibereaza toata memoria alocata pentru arbore, imagine, vectorul unde am stocat informatiile despre imagine si se inchide fisierul de out.
