# PEDAF_Tareas.

# Correcciones realizadas:

# 7_Arbol_Desplegado_Splay_Tree.

#### En esta tarea de splay tree, del archivo main.cpp, tengo "fail" en el caso 5 y 6, casos que consultan el metodo inorder():

> 5.- esperada [15 7 10 16 17]
> 
>  programa [17 16 15 7 10]
> 
> fail

> 6.- esperada [15 7 10 17]
> 
>  programa [17 15 7 10]
> 
> fail

#### La retro sobre la tarea de Splay Tree, el error lo ponen en el find, pero creo que es un error del delete (igual esto no afecta por que solo pierdo un  punto). Ahora bien en la retro se coloca donde fallo mi codigo:

```
 add success
 add success
 add success
 find success
 find success
 find success
 find success
 find success
 find success
 remove success
 remove fail
 remove success
 remove success
 remove success
 remove success
```
