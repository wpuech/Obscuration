/******************************************************************************
 * ICAR_Interns_Library
 *
 * Fichier : Paillier.hpp
 *
 * Description :
 *   Fichier source de départ Paillier_image.cpp de Bianca Jansen Van Rensburg
 *
 * Auteur : Katia Auxilien
 *
 * Mail : katia.auxilien@mail.fr
 *
 * Date : Avril 2024 - Mai 2024
 *
 *******************************************************************************/
#include <iostream>
#include <bitset>
#include <vector>
#include "../../../include/image/image_pgm.hpp"

#define BITSETSIZE 64

#ifndef PAILLIER_CRYPTOSYSTEM
#define PAILLIER_CRYPTOSYSTEM

using namespace std;

template <typename T_in, typename T_out>
class Paillier
{
public:
    Paillier(){};
    ~Paillier(){};

    /**
     *  @brief Calcul de l'exponentiation modulaire rapide.
     *  @details Calcul de l'exponentiation modulaire rapide.
     *  @param uint64_t x
     *  @param uint64_t i
     * 	@param uint64_t n
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    uint64_t fastMod_64t(uint64_t x, uint64_t e, uint64_t n)
    {
        uint64_t c = 1;
        bitset<BITSETSIZE> bits = bitset<BITSETSIZE>(e);

        for (int i = BITSETSIZE - 1; i >= 0; i--)
        {
            c = c * c % n;
            if (bits[i] & 1)
                c = c * x % n;
        }

        return c;
    };

    /**
     *  @brief Calcul du PGCD en récursif.
     *  @details Calcul du PGCD en récursif, de a et b sur 64 bit.
     *  @param uint64_t a
     * 	@param uint64_t b
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    uint64_t gcd_64t(uint64_t a, uint64_t b)
    {
        if (b == 0)
        {
            return a;
        }
        return gcd_64t(b, a % b);
    };

    /**
     *  @brief
     *  @details Calcul de l'ensemble des éléments de  g ∈ (Z/n2Z)*
     *  @param
     *  @authors Katia Auxilien
     *  @date 30/04/2024 15:51:00
     */
    std::vector<uint64_t> calc_set_same_remainder_divide_euclide_64t(uint64_t n)
    {
        std::vector<uint64_t> result;
        for (uint64_t i = 0; i < n; i++)
        {
            if (gcd_64t(i, n) == 1)
            {
                result.push_back(i);
            }
        }
        return result;
    };

    /**
     *  @brief
     *  @details Choix de g tant que (x - 1)/n ne donne pas un L(x) entier.
     *  @param
     *  @authors Katia Auxilien
     *  @date 02/05/2024
     */    uint64_t choose_g_in_vec_64t(std::vector<uint64_t> &set, const uint64_t &n, const uint64_t &lambda)
    {
        uint64_t x;
        int i_position = 0;
        uint64_t g = 0, r = 1, r2 = 1;
        while (r != 0 && r2 != 0)
        {
            i_position = rand() % set.size();
            g = set.at(i_position);
            x = fastMod_64t(g, lambda, n * n);
            r = (x - 1) % n;
            r2 = (x - 1) / n;
        }
        return g;
    };

    /**
     *  @brief Calcul de L(x).
     *  @details Calcul de L(x) nécessaire dans la génération de Mu et le déchiffrement par Paillier.
     *  @param uint64_t x
     * 	@param uint64_t n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    uint64_t L_64t(uint64_t x, uint64_t n)
    {
        return (x - 1) / n;
    };

    /**
     *  @brief Calcul du plus petit diviseur commun.
     *  @details Calcul du plus petit diviseur commun de a et b.
     *  @param uint64_t a
     * 	@param uint64_t b
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    uint64_t lcm_64t(uint64_t a, uint64_t b)
    {
        return a * b / gcd_64t(a, b);
    };

    /**
     *  @brief Calcul de l'inverse modulaire de a modulo n.
     *  @details Calcul de l'inverse modulaire de a modulo n sur 64 bit.
     *  @param uint64_t a
     * 	@param uint64_t n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */    
    uint64_t modInverse_64t(uint64_t a, uint64_t n)
    {
        a = a % n;
        for (uint64_t x = 1; x < n; x++)
        {
            if ((a * x) % n == 1)
                return x;
        }

        return 0;
    };


    /**
     *  @brief Calcul de la puissance de n de x
     *  @details Calcul de la puissance de n de x en récursif.
     *  @param uint64_t x
     * 	@param uint64_t n
     *  @authors Katia Auxilien
     *  @date 30/04/2024
     */
    uint64_t pow_uint64_t(uint64_t x, uint64_t n)
    {
        if (n == 0)
        {
            return 1;
        }
        return x * pow_uint64_t(x, n - 1);
    };


    /**
     *  @brief Génération du Mu.
     *  @details Génération du paramètre Mu nécessaire à la clé privée du chiffrement par Paillier.
     *  @param uint64_t &mu
     * 	@param const uint64_t &g
     *  @param const uint64_t &lambda
     *  @param const uint64_t &n
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    void generateMu_64t(uint64_t &mu, const uint64_t &g, const uint64_t &lambda, const uint64_t &n)
    {
        uint64_t u = fastMod_64t(g, lambda, n * n);
        uint64_t l = (u - 1) / n;
        mu = modInverse_64t(l, n);
    };

    /**
     *  @brief Génération de la clé privée du chiffrement par Paillier.
     *  @details Génération de la clé privée du chiffrement par Paillier avec des paramètres sur 64 bit.
     *  @param uint64_t &lambda
     * 	@param uint64_t &mu
     *  @param const uint64_t &p
     *  @param const uint64_t &q
     *  @param const uint64_t &n
     *  @param const uint64_t &g
     *  @authors Bianca Jansen Van Rensburg
     *  @date ?
     */
    void generatePrivateKey_64t(uint64_t &lambda, uint64_t &mu, const uint64_t &p, const uint64_t &q, const uint64_t &n, const uint64_t &g)
    {
        lambda = lcm_64t(p - 1, q - 1);

        generateMu_64t(mu, g, lambda, n);
    };

    //================ Overload and Generic programming ================//
    
    /**
     *  @overload
     *  @brief Chiffrement par paillier.
     *  @details Chiffrement par paillier d'un message m sur n bit.
     *  @param uint64_t n valeur p*q.
     * 	@param uint64_t g élément choisit dans l'ensemble (Z/n2Z)*.
     *  @param T_in m message en clair sur n bit.
     *  @return static_cast<T_in>(c) : Le message m chiffré, dont le chiffré est sur 2*n bit.
     *  @retval T_in
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
     */
    T_out paillierEncryption(uint64_t n, uint64_t g, T_in m)
    {
        uint64_t c;
        uint64_t r = rand() % n;
        while (gcd_64t(r, n) != 1 || r == 0)
        {
            r = rand() % n;
        }

        uint64_t fm1 = fastMod_64t(g, m, n * n);
        uint64_t fm2 = fastMod_64t(r, n, n * n);
        c = (fm1 * fm2) % (n * n);

        if (c >= std::numeric_limits<T_out>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans n*2 bits.");
        }
        return static_cast<T_out>(c);
    };

    /**
     *  @overload
     *  @brief Chiffrement par paillier.
     *  @details Chiffrement par paillier d'un message m sur n bit.
     *  @param uint64_t n valeur p*q, fait partie de la clé publique.
     * 	@param uint64_t g élément choisit dans l'ensemble (Z/n2Z)*, fait partie de la clé publique.
     *  @param uint64_t r élément aléatoire appartenant à l'ensemble r ∈ (Z/nZ)*.
     *  @param T_in m message en clair sur nbit.
     *  @return static_cast<T_out>(c) : Le message m chiffré, dont le chiffré est sur 2*n bit.
     *  @retval T_out
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
     */
    T_out paillierEncryption(uint64_t n, uint64_t g, T_in m, uint64_t r)
    {
        uint64_t c;

        uint64_t fm1 = fastMod_64t(g, m, n * n);
        uint64_t fm2 = fastMod_64t(r, n, n * n);
        c = (fm1 * fm2) % (n * n);

        if (c >= std::numeric_limits<T_out>::max()) {
		    throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans n*2 bits.");
        }
        return static_cast<T_out>(c);
    };

    /**
     *  @overload
     *  @brief Déchiffrement par paillier.
     *  @details Déchiffrement par paillier d'un chiffré sur 2*n bit.
     *  @param uint64_t n valeur p*q.
     * 	@param uint64_t lambda correspond au lcm(p-1,q-1), fait partie de la clé privée.
     *  @param uint64_t mu généré par la fonction generateMu_64t(...), fait partie de la clé privée.
     *  @param T_out c message chiffré sur 2*nbits.
     *  @return static_cast<T_in>(result) : Le message clair, déchiffré de c, sur n bit.
     *  @retval T_in
     *  @authors Bianca Jansen Van Rensburg, Katia Auxilien
     *  @date 13/05/2024
     */
    T_in paillierDecryption(uint64_t n, uint64_t lambda, uint64_t mu, T_out c)
    {
        uint64_t result = (((fastMod_64t(c, lambda, n * n) - 1) / n) * mu) % n;

        if (result >= std::numeric_limits<T_in>::max()) {
                throw std::runtime_error("Erreur le résultat ne peut pas être stocké dans 8 bits.");
        }
        return static_cast<T_in>(result);
    };

};

#endif // PAILLIER_CRYPTOSYSTEM