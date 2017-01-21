/* -*- mode: c++; c-basic-offset: 3 -*-
 *
 * PANDORE (PANTHEON Project)
 *
 * GREYC IMAGE
 * 6 Boulevard Mar�chal Juin
 * F-14050 Caen Cedex France
 *
 * This file is free software. You can use it, distribute it
 * and/or modify it. However, the entire risk to the quality
 * and performance of this program is with you.
 *
 *
 * For more information, refer to:
 * http://www.greyc.ensicaen.fr/EquipeImage/Pandore/
 */

/*
 * @author Alexandre Duret-Lutz - 1999-10-14
 * @author R�gis Clouard - 2001-04-10 (version 3.00)
 * @author R�gis Clouard - 2002-12-09 (version 4.00)
 * @author R�gis Clouard - 2006-04-18 (add namespace)
 */

/**
 * @file promotions.h
 * @brief Some traits that promote some deductions from two types used for Select.
 */

/*
 * This file is generated by hand ....... because of Windows95!
 * Windows95 doesn't accept the definition of template
 * specialisation with template.
 */

#ifndef __PPROMOTIONSH__
#define __PPROMOTIONSH__

namespace pandore {

/** @brief Selects a type from a specified relation
 * between 2 types T1 and T2.
 *
 * Relations are:
 * <ul>
 * <li>Select<T1,T2>::LargestUnsigned: the largest signed type between Uchar and Long returns Uchar.
 * <li>Select<T1,T2>::SmallestUnsigned: the smallest unsigned type between T1 and T2.
 * <li>Select<T1,T2>::SmallestSigned: the smallest signed type between T1 and T2.
 * <li>Select<T1,T2>::LargestSigned: the largest type between T1 and T2.
 * <li>Select<T1,T2>::Smallest: the smallest type between T1 and T2.
 * <li>Select<T1,T2>::Largest: the largest type between T1 and T2.
 *</ul>
 * For example, the following trait returns Float:
 * <pre>
 * Select< Float, Long >::Largest
 * </pre>
 * 
 * <i>Remark</i>: If nothing matches, try with the types reversed.
 * (The compiler shouldn't loop when no specialisation are found,
 * because LargestUnsigned won't be put in class before it's definition is
 * evaluated).
 */
template< typename T1, typename T2 >
struct Select {
   /* Returns the largest unsigned type between T1 and T2. */
   typedef typename Select< T2, T1 >::LargestUnsigned LargestUnsigned;
   /* Returns the largest signed type between T1 and T2. */
   typedef typename Select< T2, T1 >::LargestSigned LargestSigned;
   /* Returns the smallest unsigned type between T1 and T2. */
   typedef typename Select< T2, T1 >::SmallestUnsigned SmallestUnsigned;
   /* Returns the smallest signed type between T1 and T2. */
   typedef typename Select< T2, T1 >::SmallestSigned SmallestSigned;
   /* Returns the largest type between T1 and T2. */
   typedef typename Select< T2, T1 >::Largest Largest;
   /* Returns the smallest type between T1 and T2. */
   typedef typename Select< T2, T1 >::Smallest Smallest;
};

/* @brief Selection from a specified relation between Uchar and Uchar.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Uchar , Uchar > {
   typedef Uchar LargestUnsigned;
   typedef Char LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Uchar Largest;
   typedef Uchar Smallest;
};

/* @brief Selection from a specified relation between Uchar and Char.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Uchar , Char > {
   typedef Uchar LargestUnsigned;
   typedef Char LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Char Largest;
   typedef Uchar Smallest;
};

/* @brief Selection from a specified relation between Uchar and Short.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Uchar , Short > {
   typedef Ushort LargestUnsigned;
   typedef Short LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Short Largest;
   typedef Uchar Smallest;
};

/* @brief Selection from a specified relation between Uchar and Ushort.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Uchar , Ushort > {
   typedef Ushort LargestUnsigned;
   typedef Short LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Ushort Largest;
   typedef Uchar Smallest;
};

/* @brief Selection from a specified relation between Uchar and Long.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Uchar , Long > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Long Largest;
   typedef Uchar Smallest;
};

/* @brief Selection from a specified relation between Uchar and Ulong.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Uchar , Ulong > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Ulong Largest;
   typedef Uchar Smallest;
};

/* @brief Selection from a specified relation between Uchar and Float.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Uchar , Float > {
   typedef Float LargestUnsigned;
   typedef Float LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Float Largest;
   typedef Uchar Smallest;
};

/* @brief Selection from a specified relation between Uchar and Double.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Uchar , Double > {
   typedef Double LargestUnsigned;
   typedef Double LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Double Largest;
   typedef Uchar Smallest;
};

/* @brief Selection from a specified relation between Char and Short.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Char , Short > {
   typedef Ushort LargestUnsigned;
   typedef Short LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Short Largest;
   typedef Char Smallest;
};

/* @brief Selection from a specified relation between Char and Ushort.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Char , Ushort > {
   typedef Ushort LargestUnsigned;
   typedef Short LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Ushort Largest;
   typedef Char Smallest;
};

/* @brief Selection from a specified relation between Char and Long.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Char , Long > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Long Largest;
   typedef Char Smallest;
};

/* @brief Selection from a specified relation between Char and Ulong.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Char , Ulong > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Ulong Largest;
   typedef Char Smallest;
};

/* @brief Selection from a specified relation between Char and Float.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Char , Float > {
   typedef Float LargestUnsigned;
   typedef Float LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Float Largest;
   typedef Char Smallest;
};

/* @brief Selection from a specified relation between Char and Double.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Char , Double > {
   typedef Double LargestUnsigned;
   typedef Double LargestSigned;
   typedef Uchar SmallestUnsigned;
   typedef Char SmallestSigned;
   typedef Double Largest;
   typedef Char Smallest;
};

/* @brief Selection from a specified relation between Ushort and Ushort.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ushort , Ushort > {
   typedef Ushort LargestUnsigned;
   typedef Short LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Ushort Largest;
   typedef Ushort Smallest;
};

/* @brief Selection from a specified relation between Ushort and Short.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ushort , Short > {
   typedef Ushort LargestUnsigned;
   typedef Short LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Short Largest;
   typedef Ushort Smallest;
};

/* @brief Selection from a specified relation between Ushort and Ulong.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ushort , Ulong > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Ulong Largest;
   typedef Ushort Smallest;
};

/* @brief Selection from a specified relation between Ushort and Long.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ushort , Long > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Long Largest;
   typedef Ushort Smallest;
};

/* @brief Selection from a specified relation between Ushort and Float.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ushort , Float > {
   typedef Float LargestUnsigned;
   typedef Float LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Float Largest;
   typedef Ushort Smallest;
};

/* @brief Selection from a specified relation between Ushort and Double.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ushort , Double > {
   typedef Double LargestUnsigned;
   typedef Double LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Double Largest;
   typedef Ushort Smallest;
};

/* @brief Selection from a specified relation between SHort and Short.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Short , Short > {
   typedef Ushort LargestUnsigned;
   typedef Short LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Short Largest;
   typedef Short Smallest;
};

/* @brief Selection from a specified relation between Short and Long.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Short , Long > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Long Largest;
   typedef Short Smallest;
};

/* @brief Selection from a specified relation between Short and Ulong.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Short , Ulong > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Long Largest;
   typedef Short Smallest;
};

/* @brief Selection from a specified relation between Short and Float.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Short , Float > {
   typedef Float LargestUnsigned;
   typedef Float LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Float Largest;
   typedef Short Smallest;
};

/* @brief Selection from a specified relation between Short and Double.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Short , Double > {
   typedef Double LargestUnsigned;
   typedef Double LargestSigned;
   typedef Ushort SmallestUnsigned;
   typedef Short SmallestSigned;
   typedef Double Largest;
   typedef Short Smallest;
};

/* @brief Selection from a specified relation between Ulong and Ulong.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ulong , Ulong > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Ulong SmallestUnsigned;
   typedef Long SmallestSigned;
   typedef Ulong Largest;
   typedef Ulong Smallest;
};

/* @brief Selection from a specified relation between Ulong and Long.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ulong , Long > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Ulong SmallestUnsigned;
   typedef Long SmallestSigned;
   typedef Long Largest;
   typedef Ulong Smallest;
};

/* @brief Selection from a specified relation between Ulong and Float.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ulong , Float > {
   typedef Float LargestUnsigned;
   typedef Float LargestSigned;
   typedef Ulong SmallestUnsigned;
   typedef Long SmallestSigned;
   typedef Float Largest;
   typedef Ulong Smallest;
};

/* @brief Selection from a specified relation between Ulong and Double.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Ulong , Double > {
   typedef Double LargestUnsigned;
   typedef Double LargestSigned;
   typedef Ulong SmallestUnsigned;
   typedef Long SmallestSigned;
   typedef Double Largest;
   typedef Ulong Smallest;
};


/* @brief Selection from a specified relation between Long and Long.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Long , Long > {
   typedef Ulong LargestUnsigned;
   typedef Long LargestSigned;
   typedef Ulong SmallestUnsigned;
   typedef Long SmallestSigned;
   typedef Long Largest;
   typedef Long Smallest;
};

/* @brief Selection from a specified relation between Long and Float.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Long , Float > {
   typedef Float LargestUnsigned;
   typedef Float LargestSigned;
   typedef Ulong SmallestUnsigned;
   typedef Long SmallestSigned;
   typedef Float Largest;
   typedef Long Smallest;
};

/* @brief Selection from a specified relation between Long and Double.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Long , Double > {
   typedef Double LargestUnsigned;
   typedef Double LargestSigned;
   typedef Ulong SmallestUnsigned;
   typedef Long SmallestSigned;
   typedef Double Largest;
   typedef Long Smallest;
};

/* @brief Selection from a specified relation between Float and Float.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Float , Float > {
   typedef Float LargestUnsigned;
   typedef Float LargestSigned;
   typedef Float SmallestUnsigned;
   typedef Float SmallestSigned;
   typedef Float Largest;
   typedef Float Smallest;
};

/* @brief Selection from a specified relation between Float and Double.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Float , Double > {
   typedef Double LargestUnsigned;
   typedef Double LargestSigned;
   typedef Float SmallestUnsigned;
   typedef Float SmallestSigned;
   typedef Double Largest;
   typedef Float Smallest;
};

/* @brief Selection from a specified relation between Double and Double.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Double , Double > {
   typedef Double LargestUnsigned;
   typedef Double LargestSigned;
   typedef Double SmallestUnsigned;
   typedef Double SmallestSigned;
   typedef Double Largest;
   typedef Double Smallest;
};

/*
 * Images (IMG-1D)
 */

/* @brief Selection from a specified relation between Img1duc and Img1duc.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img1duc, Img1duc > {
   typedef Img1duc LargestUnsigned;
   typedef Img1duc SmallestUnsigned;
   typedef Img1dsl LargestSigned;
   typedef Img1dsl SmallestSigned;
   typedef Img1duc Largest;
   typedef Img1duc Smallest;
};


/* @brief Selection from a specified relation between Img1duc and Img1dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img1duc, Img1dsl > {
   typedef Img1dsl LargestUnsigned;
   typedef Img1duc SmallestUnsigned;
   typedef Img1dsl LargestSigned;
   typedef Img1dsl SmallestSigned;
   typedef Img1dsl Largest;
   typedef Img1duc Smallest;
};


/* @brief Selection from a specified relation between Img1duc and Img1dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img1duc, Img1dsf > {
   typedef Img1dsf LargestUnsigned;
   typedef Img1dsf LargestSigned;
   typedef Img1dsf SmallestSigned;
   typedef Img1duc SmallestUnsigned;
   typedef Img1dsf Largest;
   typedef Img1duc Smallest;
};


// Signed Long

/* @brief Selection from a specified relation between Img1dsl and Img1dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img1dsl, Img1dsl > {
   typedef Img1dsl LargestUnsigned;
   typedef Img1dsl LargestSigned;
   typedef Img1dsl SmallestUnsigned;
   typedef Img1dsl SmallestSigned;
   typedef Img1dsl Largest;
   typedef Img1dsl Smallest;
};

/* @brief Selection from a specified relation between Img1dsl and Img1dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img1dsl, Img1dsf > {
   typedef Img1dsf LargestUnsigned;
   typedef Img1dsf LargestSigned;
   typedef Img1dsl SmallestUnsigned;
   typedef Img1dsl SmallestSigned;
   typedef Img1dsf Largest;
   typedef Img1dsl Smallest;
};

/* @brief Selection from a specified relation between Img1dsf and Img1dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img1dsf, Img1dsf > {
   typedef Img1dsf LargestUnsigned;
   typedef Img1dsf LargestSigned;
   typedef Img1dsf SmallestUnsigned;
   typedef Img1dsf SmallestSigned;
   typedef Img1dsf Largest;
   typedef Img1dsf Smallest;
};

/*
 * Images (IMG-2D)
 */

/* 
 * Unsigned Char
 */

/* @brief Selection from a specified relation between Img2duc and Img2duc.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img2duc, Img2duc > {
   typedef Img2dsl LargestSigned;
   typedef Img2duc LargestUnsigned;
   typedef Img2duc SmallestUnsigned;
   typedef Img2dsl SmallestSigned;
   typedef Img2duc Largest;
   typedef Img2duc Smallest;
};

/* @brief Selection from a specified relation between Img2duc and Img2dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img2duc, Img2dsl > {
   typedef Img2dsl LargestUnsigned;
   typedef Img2dsl LargestSigned;
   typedef Img2duc SmallestUnsigned;
   typedef Img2dsl SmallestSigned;
   typedef Img2dsl Largest;
   typedef Img2duc Smallest;
};

/* @brief Selection from a specified relation between Img2duc and Img2dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img2duc, Img2dsf > {
   typedef Img2dsf LargestUnsigned;
   typedef Img2dsf LargestSigned;
   typedef Img2duc SmallestUnsigned;
   typedef Img2dsf SmallestSigned;
   typedef Img2dsf Largest;
   typedef Img2duc Smallest;
};


// Signed Long

/* @brief Selection from a specified relation between Img2dsl and Img2dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img2dsl, Img2dsl > {
   typedef Img2dsl LargestUnsigned;
   typedef Img2dsl LargestSigned;
   typedef Img2dsl SmallestUnsigned;
   typedef Img2dsl SmallestSigned;
   typedef Img2dsl Largest;
   typedef Img2dsl Smallest;
};

/* @brief Selection from a specified relation between Img2dsl and Img2dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img2dsl, Img2dsf > {
   typedef Img2dsf LargestUnsigned;
   typedef Img2dsf LargestSigned;
   typedef Img2dsl SmallestUnsigned;
   typedef Img2dsl SmallestSigned;
   typedef Img2dsf Largest;
   typedef Img2dsl Smallest;
};

/* @brief Selection from a specified relation between Img2dsf and Img2dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img2dsf, Img2dsf > {
   typedef Img2dsf LargestUnsigned;
   typedef Img2dsf LargestSigned;
   typedef Img2dsf SmallestUnsigned;
   typedef Img2dsf SmallestSigned;
   typedef Img2dsf Largest;
   typedef Img2dsf Smallest;
};

/*
 * Images (IMG-3D)
 */

// Unsigned Char

/* @brief Selection from a specified relation between Img3duc and Img3duc.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img3duc, Img3duc > {
   typedef Img3duc LargestUnsigned;
   typedef Img3dsl LargestSigned;
   typedef Img3duc SmallestUnsigned;
   typedef Img3dsl SmallestSigned;
   typedef Img3duc Largest;
   typedef Img3duc Smallest;
};


/* @brief Selection from a specified relation between Img3duc and Img2dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img3duc, Img3dsl > {
   typedef Img3dsl LargestUnsigned;
   typedef Img3dsl LargestSigned;
   typedef Img3duc SmallestUnsigned;
   typedef Img3dsl SmallestSigned;
   typedef Img3dsl Largest;
   typedef Img3duc Smallest;
};

/* @brief Selection from a specified relation between Img3duc and Img3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img3duc, Img3dsf > {
   typedef Img3dsf LargestUnsigned;
   typedef Img3dsf LargestSigned;
   typedef Img3duc SmallestUnsigned;
   typedef Img3dsf SmallestSigned;
   typedef Img3dsf Largest;
   typedef Img3duc Smallest;
};

// Signed Long

/* @brief Selection from a specified relation between Img3dsl and Img3dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img3dsl, Img3dsl > {
   typedef Img3dsl LargestUnsigned;
   typedef Img3dsl LargestSigned;
   typedef Img3dsl SmallestUnsigned;
   typedef Img3dsl SmallestSigned;
   typedef Img3dsl Largest;
   typedef Img3dsl Smallest;
};

/* @brief Selection from a specified relation between Img3dsl and Img3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img3dsl, Img3dsf > {
   typedef Img3dsf LargestUnsigned;
   typedef Img3dsf LargestSigned;
   typedef Img3dsl SmallestUnsigned;
   typedef Img3dsl SmallestSigned;
   typedef Img3dsf Largest;
   typedef Img3dsl Smallest;
};


/* @brief Selection from a specified relation between Img3dsf and Img3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Img3dsf, Img3dsf > {
   typedef Img3dsf LargestUnsigned;
   typedef Img3dsf LargestSigned;
   typedef Img3dsf SmallestUnsigned;
   typedef Img3dsf SmallestSigned;
   typedef Img3dsf Largest;
   typedef Img3dsf Smallest;
};

/*
 * Images (IMC-2D)
 */

/* @brief Selection from a specified relation between Imc2duc and Imc2duc.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Imc2duc, Imc2duc > {
   typedef Imc2duc LargestUnsigned;
   typedef Imc2dsl LargestSigned;
   typedef Imc2duc SmallestUnsigned;
   typedef Imc2dsl SmallestSigned;
   typedef Imc2duc Largest;
   typedef Imc2duc Smallest;
};

/* @brief Selection from a specified relation between Imc2duc and Imc2dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Imc2duc, Imc2dsl > {
   typedef Imc2dsl LargestUnsigned;
   typedef Imc2dsl LargestSigned;
   typedef Imc2duc SmallestUnsigned;
   typedef Imc2dsl SmallestSigned;
   typedef Imc2dsl Largest;
   typedef Imc2duc Smallest;
};

/* @brief Selection from a specified relation between Imc2duc and Imc2dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc2duc, Imc2dsf > {
   typedef Imc2dsf LargestUnsigned;
   typedef Imc2dsf LargestSigned;
   typedef Imc2duc SmallestUnsigned;
   typedef Imc2dsf SmallestSigned;
   typedef Imc2dsf Largest;
   typedef Imc2duc Smallest;
};

// Signed Long

/* @brief Selection from a specified relation between Imc2dsl and Imc2dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc2dsl, Imc2dsl > {
   typedef Imc2dsl LargestUnsigned;
   typedef Imc2dsl LargestSigned;
   typedef Imc2dsl SmallestUnsigned;
   typedef Imc2dsl SmallestSigned;
   typedef Imc2dsl Largest;
   typedef Imc2dsl Smallest;
};

/* @brief Selection from a specified relation between Imc2dsl and Imc2dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc2dsl, Imc2dsf > {
   typedef Imc2dsf LargestUnsigned;
   typedef Imc2dsf LargestSigned;
   typedef Imc2dsl SmallestUnsigned;
   typedef Imc2dsl SmallestSigned;
   typedef Imc2dsf Largest;
   typedef Imc2dsl Smallest;
};

/* @brief Selection from a specified relation between Imc2dsf and Imc2dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc2dsf, Imc2dsf > {
   typedef Imc2dsf LargestUnsigned;
   typedef Imc2dsf LargestSigned;
   typedef Imc2dsf SmallestUnsigned;
   typedef Imc2dsf SmallestSigned;
   typedef Imc2dsf Largest;
   typedef Imc2dsf Smallest;
};

/*
 * Images (IMC-3D)
 */

// Unsigned Char

/* @brief Selection from a specified relation between Imc3duc and Imc3duc.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc3duc, Imc3duc > {
   typedef Imc3duc LargestUnsigned;
   typedef Imc3dsl LargestSigned;
   typedef Imc3duc SmallestUnsigned;
   typedef Imc3dsl SmallestSigned;
   typedef Imc3duc Largest;
   typedef Imc3duc Smallest;
};

/* @brief Selection from a specified relation between Imc3duc and Imc3dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc3duc, Imc3dsl > {
   typedef Imc3dsl LargestUnsigned;
   typedef Imc3dsl LargestSigned;
   typedef Imc3duc SmallestUnsigned;
   typedef Imc3dsl SmallestSigned;
   typedef Imc3dsl Largest;
   typedef Imc3duc Smallest;
};

/* @brief Selection from a specified relation between Imc3duc and Imc3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc3duc, Imc3dsf > {
   typedef Imc3dsf LargestUnsigned;
   typedef Imc3dsf LargestSigned;
   typedef Imc3duc SmallestUnsigned;
   typedef Imc3dsl SmallestSigned;
   typedef Imc3dsf Largest;
   typedef Imc3duc Smallest;
};

// Signed Long

/* @brief Selection from a specified relation between Imc3dsl and Imc3dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc3dsl, Imc3dsl > {
   typedef Imc3dsl LargestUnsigned;
   typedef Imc3dsl LargestSigned;
   typedef Imc3dsl SmallestUnsigned;
   typedef Imc3dsl SmallestSigned;
   typedef Imc3dsl Largest;
   typedef Imc3dsl Smallest;
};

/* @brief Selection from a specified relation between Imc3dsl and Imc3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc3dsl, Imc3dsf > {
   typedef Imc3dsf LargestUnsigned;
   typedef Imc3dsf LargestSigned;
   typedef Imc3dsl SmallestUnsigned;
   typedef Imc3dsl SmallestSigned;
   typedef Imc3dsf Largest;
   typedef Imc3dsl Smallest;
};

/* @brief Selection from a specified relation between Imc3dsf and Imc3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imc3dsf, Imc3dsf > {
   typedef Imc3dsf LargestUnsigned;
   typedef Imc3dsf LargestSigned;
   typedef Imc3dsf SmallestUnsigned;
   typedef Imc3dsf SmallestSigned;
   typedef Imc3dsf Largest;
   typedef Imc3dsf Smallest;
};

/*
 * Regions.
 */
/* @brief Selection from a specified relation between Reg1d and Reg1d.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Reg1d , Reg1d > {
   typedef Reg1d LargestUnsigned;
   typedef Reg1d LargestSigned;
   typedef Reg1d SmallestUnsigned;
   typedef Reg1d SmallestSigned;
   typedef Reg1d Unsigned;
   typedef Reg1d Signed;
};

/* @brief Selection from a specified relation between Reg2d and Reg2d.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Reg2d , Reg2d > {
   typedef Reg2d LargestUnsigned;
   typedef Reg2d LargestSigned;
   typedef Reg2d SmallestUnsigned;
   typedef Reg2d SmallestSigned;
   typedef Reg2d Unsigned;
   typedef Reg2d Signed;
};

/* @brief Selection from a specified relation between Reg3d and Reg3d.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Reg3d , Reg3d > {
   typedef Reg3d LargestUnsigned;
   typedef Reg3d LargestSigned;
   typedef Reg3d SmallestUnsigned;
   typedef Reg3d SmallestSigned;
   typedef Reg3d Unsigned;
   typedef Reg3d Signed;
};

/*
 * Graph (GRAPH - 2D)
 */

/* @brief Selection from a specified relation between Graph2d and Graph2d.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Graph2d , Graph2d > {
   typedef Graph2d LargestUnsigned;
   typedef Graph2d LargestSigned;
   typedef Graph2d SmallestUnsigned;
   typedef Graph2d SmallestSigned;
   typedef Graph2d Unsigned;
   typedef Graph2d Signed;
};

/* @brief Selection from a specified relation between Graph3d and Graph3d.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template<> struct Select< Graph3d , Graph3d > {
   typedef Graph3d LargestUnsigned;
   typedef Graph3d LargestSigned;
   typedef Graph3d SmallestUnsigned;
   typedef Graph3d SmallestSigned;
   typedef Graph3d Unsigned;
   typedef Graph3d Signed;
};

/*
 * Images (IMX-1D)
 */

/* @brief Selection from a specified relation between Imx1duc and Imx1duc.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx1duc, Imx1duc > {
   typedef Imx1duc LargestUnsigned;
   typedef Imx1dsl LargestSigned;
   typedef Imx1duc SmallestUnsigned;
   typedef Imx1dsl SmallestSigned;
   typedef Imx1duc Largest;
   typedef Imx1duc Smallest;
};


/* @brief Selection from a specified relation between Imx1duc and Imx1dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx1duc, Imx1dsl > {
   typedef Imx1dsl LargestUnsigned;
   typedef Imx1dsl LargestSigned;
   typedef Imx1duc SmallestUnsigned;
   typedef Imx1dsl SmallestSigned;
   typedef Imx1dsl Largest;
   typedef Imx1duc Smallest;
};

/* @brief Selection from a specified relation between Imx1duc and Imx1dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx1duc, Imx1dsf > {
   typedef Imx1dsf LargestUnsigned;
   typedef Imx1dsf LargestSigned;
   typedef Imx1duc SmallestUnsigned;
   typedef Imx1dsl SmallestSigned;
   typedef Imx1dsf Largest;
   typedef Imx1duc Smallest;
};

// Signed Long

/* @brief Selection from a specified relation between Imx1dsl and Imx1dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx1dsl, Imx1dsl > {
   typedef Imx1dsl LargestUnsigned;
   typedef Imx1dsl LargestSigned;
   typedef Imx1dsl SmallestUnsigned;
   typedef Imx1dsl SmallestSigned;
   typedef Imx1dsl Largest;
   typedef Imx1dsl Smallest;
};

/* @brief Selection from a specified relation between Imx1dsl and Imx1dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx1dsl, Imx1dsf > {
   typedef Imx1dsf LargestUnsigned;
   typedef Imx1dsf LargestSigned;
   typedef Imx1dsl SmallestUnsigned;
   typedef Imx1dsl SmallestSigned;
   typedef Imx1dsf Largest;
   typedef Imx1dsl Smallest;
};

/* @brief Selection from a specified relation between Imx1dsf and Imx1dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx1dsf, Imx1dsf > {
   typedef Imx1dsf LargestUnsigned;
   typedef Imx1dsf LargestSigned;
   typedef Imx1dsf SmallestUnsigned;
   typedef Imx1dsf SmallestSigned;
   typedef Imx1dsf Largest;
   typedef Imx1dsf Smallest;
};

/*
 * Images (IMX-2D)
 */

/* @brief Selection from a specified relation between Imx2duc and Imx2duc.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx2duc, Imx2duc > {
   typedef Imx2duc LargestUnsigned;
   typedef Imx2dsl LargestSigned;
   typedef Imx2duc SmallestUnsigned;
   typedef Imx2dsl SmallestSigned;
   typedef Imx2duc Largest;
   typedef Imx2duc Smallest;
};

/* @brief Selection from a specified relation between Imx2duc and Imx2dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx2duc, Imx2dsl > {
   typedef Imx2dsl LargestUnsigned;
   typedef Imx2dsl LargestSigned;
   typedef Imx2duc SmallestUnsigned;
   typedef Imx2dsl SmallestSigned;
   typedef Imx2dsl Largest;
   typedef Imx2duc Smallest;
};

/* @brief Selection from a specified relation between Imx2duc and Imx2dusf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx2duc, Imx2dsf > {
   typedef Imx2dsf LargestUnsigned;
   typedef Imx2dsf LargestSigned;
   typedef Imx2duc SmallestUnsigned;
   typedef Imx2dsl SmallestSigned;
   typedef Imx2dsf Largest;
   typedef Imx2duc Smallest;
};

// Signed Long

/* @brief Selection from a specified relation between Imx2dsl and Imx2dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx2dsl, Imx2dsl > {
   typedef Imx2dsl LargestUnsigned;
   typedef Imx2dsl LargestSigned;
   typedef Imx2dsl SmallestUnsigned;
   typedef Imx2dsl SmallestSigned;
   typedef Imx2dsl Largest;
   typedef Imx2dsl Smallest;
};

/* @brief Selection from a specified relation between Imx2dsl and Imx2dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx2dsl, Imx2dsf > {
   typedef Imx2dsf LargestUnsigned;
   typedef Imx2dsf LargestSigned;
   typedef Imx2dsl SmallestUnsigned;
   typedef Imx2dsl SmallestSigned;
   typedef Imx2dsf Largest;
   typedef Imx2dsl Smallest;
};

/* @brief Selection from a specified relation between Imx2dsf and Imx2dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx2dsf, Imx2dsf > {
   typedef Imx2dsf LargestUnsigned;
   typedef Imx2dsf LargestSigned;
   typedef Imx2dsf SmallestUnsigned;
   typedef Imx2dsf SmallestSigned;
   typedef Imx2dsf Largest;
   typedef Imx2dsf Smallest;
};

// Signed Double (unsigned double doesn't exist!)

/*
 * Images (IMG-3D)
 */

/* @brief Selection from a specified relation between Imx3duc and Imx3duc.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx3duc, Imx3duc > {
   typedef Imx3duc LargestUnsigned;
   typedef Imx3dsl LargestSigned;
   typedef Imx3duc SmallestUnsigned;
   typedef Imx3dsl SmallestSigned;
   typedef Imx3duc Largest;
   typedef Imx3duc Smallest;
};

/* @brief Selection from a specified relation between Imx3duc and Imx3dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx3duc, Imx3dsl > {
   typedef Imx3dsl LargestUnsigned;
   typedef Imx3dsl LargestSigned;
   typedef Imx3duc SmallestUnsigned;
   typedef Imx3dsl SmallestSigned;
   typedef Imx3dsl Largest;
   typedef Imx3duc Smallest;
};

/* @brief Selection from a specified relation between Imx3duc and Imx3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx3duc, Imx3dsf > {
   typedef Imx3dsf LargestUnsigned;
   typedef Imx3dsf LargestSigned;
   typedef Imx3duc SmallestUnsigned;
   typedef Imx3dsl SmallestSigned;
   typedef Imx3dsf Largest;
   typedef Imx3duc Smallest;
};

// Signed Long

/* @brief Selection from a specified relation between Imx3dsl and Imx3dsl.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx3dsl, Imx3dsl > {
   typedef Imx3dsl LargestUnsigned;
   typedef Imx3dsl LargestSigned;
   typedef Imx3dsl SmallestUnsigned;
   typedef Imx3dsl SmallestSigned;
   typedef Imx3dsl Largest;
   typedef Imx3dsl Smallest;
};

/* @brief Selection from a specified relation between Imx3dsl and Imx3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx3dsl, Imx3dsf > {
   typedef Imx3dsf LargestUnsigned;
   typedef Imx3dsf LargestSigned;
   typedef Imx3dsl SmallestUnsigned;
   typedef Imx3dsl SmallestSigned;
   typedef Imx3dsf Largest;
   typedef Imx3dsl Smallest;
};

/* @brief Selection from a specified relation between Imx3dsf and Imx3dsf.
 *
 * Returns the type according to a specified relation between
 * the two types.
 */
template< > struct Select< Imx3dsf, Imx3dsf > {
   typedef Imx3dsf LargestUnsigned;
   typedef Imx3dsf LargestSigned;
   typedef Imx3dsf SmallestUnsigned;
   typedef Imx3dsf SmallestSigned;
   typedef Imx3dsf Largest;
   typedef Imx3dsf Smallest;
};

} //End of pandore:: namespace

#endif // __PPROMOTIONSH__