#include "../../include/ImageBase.h"
#include "../../include/obscurationCommon.h"
#include "../../include/obscurationPGM.h"
#include "../../include/filesystemPGM.h"
#include "../../include/filesystemCommon.h"
#include "../../include/AES.h"
extern "C"
{
    #include "../../include/image_ppm.h"
}

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#define FILE_EXT ".pgm"

/**
 * Pour utiliser ce programme, les images contenues dans vos fichiers doivent avoir le nom 'nomdudossier_ (i)' i allant de 0 à n images.
 **/
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : directory\n");
        return 1;
    }

    char t_cImagePath[200];
    std::string sFolderPath = argv[1];
    std::string sImgClass = getLastDirectoryName(sFolderPath);
    std::string sNewFolderPath;
    std::vector<std::string> v_sImagePaths;
/*
    // ============================ DEBUT Blurring ============================ //
    std::cout << "Debut floutage moyenneur..."
              << "\n";

    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/blurring/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        std::vector<ImageBase> v_ibImgOut;
        newAverageBlurring_PGM(ibImgInResized, v_ibImgOut);

        for (int cpt = 1; cpt <= 101; cpt += 2)
        {
            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());
            v_ibImgOut[cpt / 2].save(t_cImagePath);
        }
        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin floutage moyenneur"
              << "\n";
    // ============================ FIN Blurring ============================ //

    // ============================ DEBUT Scrambling ============================ //
    std::cout << "Debut melange par region..."
              << "\n";

    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/scrambling/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int cpt = 1; cpt <= 50; ++cpt)
        {
            ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());

            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            scrambling_PGM(ibImgInResized, ibImgOut, cpt, cpt);
            ibImgOut.save(t_cImagePath);
        }
        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin melange par region"
              << "\n";
    // ============================ FIN Scrambling ============================ //

    // ============================ DEBUT Pixelisation ============================ //
    std::cout << "Debut moyenneur par r�gion..."
              << "\n";

    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/pixeliser/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int cpt = 1; cpt <= 50; ++cpt)
        {
            ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());

            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            averageByRegion_PGM(ibImgInResized, ibImgOut, cpt, cpt);
            ibImgOut.save(t_cImagePath);
        }
        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin moyenneur par region"
              << "\n";
    // ============================ FIN Pixelisation ============================ //

    // ============================ DEBUT Chiffrement sélectif ============================ //
    std::cout << "\t"
              << "Chiffrement sélectif"
              << "\n";

    // ============== DEBUT Chiffrement sélectif par bit individuel ============== //

    std::cout << "Debut chiffrement selectif par bit individuel..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/individual/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        selectiveIndividualEncryption_PGM(ibImgInResized, t_ibImages);

        for (int cpt = 0; cpt <= 7; ++cpt)
        {

            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            t_ibImages[cpt].save(t_cImagePath);
        }
        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement selectif par bit individuel."
              << "\n";
    // ============== FIN Chiffrement sélectif par bit individuel ============== //

    // ============== DEBUT Chiffrement sélectif par bit consecutif MSB à LSB ============== //

    std::cout << "Debut chiffrement selectif par bit consecutif MSB à LSB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/consecutive-MSB2LSB/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        selectiveProgressiveEncryption_PGM(ibImgInResized, t_ibImages, true);

        for (int cpt = 0; cpt <= 7; ++cpt)
        {
            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            t_ibImages[cpt].save(t_cImagePath);
        }
        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement selectif par bit consecutif MSB à LSB."
              << "\n";
    // ============== FIN Chiffrement sélectif par bit consecutif MSB à LSB ============== //

    // ============== DEBUT Chiffrement sélectif par bit consecutif MSB à LSB ============== //

    std::cout << "Debut chiffrement selectif par bit consecutif LSB à MSB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/consecutive-LSB2MSB/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        ImageBase t_ibImages[8] = {ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor()),
                                   ImageBase(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor())};
        selectiveProgressiveEncryption_PGM(ibImgInResized, t_ibImages, false);

        for (int cpt = 0; cpt <= 7; ++cpt)
        {
            std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(cpt) + FILE_EXT;
            std::strcpy(t_cImagePath, sImOutPath.c_str());

            t_ibImages[cpt].save(t_cImagePath);
        }
        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement selectif par bit consecutif LSB à MSB."
              << "\n";
    // ============== FIN Chiffrement sélectif par bit consecutif MSB à LSB ============== //

    // ============== DEBUT Chiffrement sélectif par bit groupé ============== //

    std::cout << "Debut chiffrement selectif par bit groupé..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/ranged/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        ImageBase ibImgInOriginal;
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImagePath, sImInPath.c_str());
        ibImgInOriginal.load(t_cImagePath);
        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        ImageBase ibImgInResized(299, 299, false);
        bilinearRedim299_PGM(ibImgInOriginal, ibImgInResized);

        for (int nGSize = 1; nGSize <= 8; ++nGSize)
        {
            std::vector<std::vector<int>> v_nBitGroup;
            genBitsGroups(v_nBitGroup, nGSize);
            for (int i = 0; i < v_nBitGroup.size(); ++i)
            {
                int nGroup[8];
                intVec2intArray(v_nBitGroup[i], nGroup);
                ImageBase ibImgOut(ibImgInResized.getWidth(), ibImgInResized.getHeight(), ibImgInResized.getColor());
                selectiveGroupEncryption_PGM(ibImgInResized, ibImgOut, nGroup, nGSize);

                std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + "_" + std::to_string(nGSize) + FILE_EXT;
                std::strcpy(t_cImagePath, sImOutPath.c_str());

                ibImgOut.save(t_cImagePath);
            }
        }
        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement selectif par bit groupé."
              << "\n";
    // ============== FIN Chiffrement sélectif par bit groupé============== //
    // ============================ FIN Chiffrement sélectif ============================ //
*/
    // ============================ DEBUT Chiffrement AES ============================ //
    std::cout << "\t"
              << "Chiffrement AES"
              << "\n";

    char t_cImageInPath[200], t_cImageOutPath[200];

    // ============== DEBUT Chiffrement AES ECB ============== //

    std::cout << "Debut chiffrement AES mode ECB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/ECB/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = {0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b};

        oImgOut = aes.EncryptECB(oImgIn, nTaille, key);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement AES mode ECB"
              << "\n";

    // ============== FIN Chiffrement AES ECB ============== //

    // ============== DEBUT Chiffrement AES CBC ============== //
    std::cout << "Debut chiffrement AES mode CBC..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CBC/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = { 0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b };
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCBC(oImgIn, nTaille, key,iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement AES mode CBC"
              << "\n";
    // ============== FIN Chiffrement AES CBC ============== //

    // ============== DEBUT Chiffrement AES CTR ============== //

    std::cout << "Debut chiffrement AES mode CTR..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CTR/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = { 0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b };
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCTR(oImgIn, nTaille, key,iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement AES mode CTR"
              << "\n";

    // ============== FIN Chiffrement AES CTR ============== //

    // ============== DEBUT Chiffrement AES CFB ============== //
    
    std::cout << "Debut chiffrement AES mode CFB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/CFB/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = { 0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b };
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptCFB(oImgIn, nTaille, key,iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement AES mode CFB"
              << "\n";

    // ============== FIN Chiffrement AES CFB ============== //

    // ============== DEBUT Chiffrement AES OFB ============== //

    std::cout << "Debut chiffrement AES mode OFB..."
              << "\n";
    std::strcpy(t_cImagePath, sFolderPath.c_str());
    sNewFolderPath = getProgramFolderPath(argv[0]) + "/obscuredPGM/encryption/AES/OFB/" + sImgClass;
    getFilePathsOfPGMFilesFromFolder(v_sImagePaths, t_cImagePath);

    for (int nImg_cpt = 0; nImg_cpt < v_sImagePaths.size(); ++nImg_cpt)
    {
        std::string sImInPath = sFolderPath + '/' + sImgClass + "_ (" + std::to_string(nImg_cpt + 1) + ")" + FILE_EXT;
        std::strcpy(t_cImageInPath, sImInPath.c_str());

        std::cout << "Image n°" << nImg_cpt + 1 << " en cours ... "
                  << "\n";

        std::string sNewImgPath = sNewFolderPath + "/" + std::to_string(nImg_cpt);
        createDirectoryIfNotExists(sNewImgPath);

        std::string sImOutPath = sNewImgPath + "/" + sImgClass + "_" + std::to_string(nImg_cpt) + FILE_EXT;
        std::strcpy(t_cImageOutPath, sImOutPath.c_str());

        int nH, nW, nTaille;
        OCTET *oImgIn, *oImgOut;

        lire_nb_lignes_colonnes_image_pgm(t_cImageInPath, &nH, &nW);
        nTaille = nH * nW;

        allocation_tableau(oImgIn, OCTET, nTaille);
        lire_image_pgm(t_cImageInPath, oImgIn, nH * nW);
        allocation_tableau(oImgOut, OCTET, nTaille);

        AES aes(AESKeyLength::AES_128);

        unsigned char key[] = { 0x96, 0x39, 0xb4, 0xfa, 0xe6, 0x52, 0xd1, 0x84, 0x59, 0x97, 0x3b, 0xd9, 0x26, 0xde, 0x71, 0x5b };
        unsigned char iv[] = {0xd7, 0x7a, 0x79, 0xe3, 0xb2, 0xc5, 0x93, 0x7d, 0x30, 0x69, 0xc4, 0x28, 0x59, 0x62, 0xa3, 0xc8};

        oImgOut = aes.EncryptOFB(oImgIn, nTaille, key,iv);

        ecrire_image_pgm(t_cImageOutPath, oImgOut, nH, nW);
        free(oImgIn);

        std::cout << "Image " << nImg_cpt + 1 << " sur " << v_sImagePaths.size() << "\n";
    }
    std::cout << "Fin chiffrement AES mode OFB"
              << "\n";


    // ============== FIN Chiffrement AES OFB ============== //


    // ============================ FIN Chiffrement AES ============================ //

    return 0;
}