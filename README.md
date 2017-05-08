![](http://www.uic.unn.ru/~zny/skeleton/.tric.gif)

# Skeleton: Implementation of Double Description Method
Converx Hull Problem and Solving Systems of Linear Inequalities

Because the original skeleton package has not been updated for a quite long time. And I found it can not been compiled under Linux system because of two bugs. Thus I fixed the bugs and re-distribution the code here.

For more information, please read http://www.uic.unn.ru/~zny/skeleton/.
Skeleton is a new fast implementation of Double Description Method (DDM) [1] for generating all extreme rays of a polyhedral cone and, consequently, for solving the vertex and facet enumeration problems for convex polyhedra. Using Skeleton you can solve convex hull problem in d-dimensinal space. Also, you can find all solutions to a system of linear inequalities.
New enhancements [2] make Skeleton very competitive in comparison with other implementations of DDM and other methods for solving these problems.

Float, integer and arbitrary precision integer arithmetics is supported. The implementation uses Arageli library for exact computation.

Please cite [2] in your publication if you use Skeleton.

A descendant of Skeleton is S. Bastrakov's qskeleton that uses a lot of new enchancements [3]. We note that not all features of skeleton is supported in qskeleton.

* Motzkin T.S., Raiffa H., Thompson G.L., Thrall R.M. The double description method. In H. W. Kuhn and A. W. Tucker, editors, Contributions to the Theory of Games - Volume II, number 28 in Annals of Mathematics Studies, pages 51-73. Princeton University Press, Princeton, New Jersey, 1953.
* Золотых Н.Ю. Новая модификация метода двойного описания для построения остова многогранного конуса // Журнал вычислительной математики и математической физики. - 2012. - Т. 52, N 1. - С. 153-163. pdf English transl.: Zolotykh N.Yu. New modification of the double description method for constructing the skeleton of a polyhedral cone // Computational mathematics and mathematical physics. - 2012. - V. 52, N.1. - P.146-156. pdf
* Bastrakov S.I., Zolotykh N.Yu. Application of the Quickhull algorithm's principles to the double description method // Numerical Methods and Programming/ 2011. V. 12. P. 232-237 (in Russian)
