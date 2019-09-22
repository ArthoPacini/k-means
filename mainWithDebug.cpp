#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <algorithm>

#include "Vec3.h"

template <typename T>
T getRandomNumber(const T min = std::numeric_limits<T>::min(), const T max = std::numeric_limits<T>::max())
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<T> random_distribution(min, max);
    return random_distribution(mt);
}

std::vector<Vec3<double> > getRandomGravityPoints(const std::vector<Vec3<double> > & pontos, const std::uint32_t k_groups)
{
    if(k_groups >= pontos.size())
        return pontos;
    
    std::vector<std::uint32_t> randomPoints;
    randomPoints.reserve(k_groups);

    for(std::uint32_t i = 0; i < k_groups; ++i)
    {
        std::uint32_t point;

        do
            point = getRandomNumber<std::uint32_t>(0, pontos.size() - 1);
        while(std::find(randomPoints.begin(), randomPoints.end(), point) != randomPoints.end());

        randomPoints.emplace_back(point);
    }

    std::vector<Vec3<double> > output;
    output.reserve(k_groups);
    for(const auto & r : randomPoints)
        output.emplace_back(pontos[r]);

    return output;
}

void assignDataPointToCluster(std::vector<std::vector<Vec3<double>>> & vectorOfClusters, std::vector<Vec3<double>> & gravityPoints, Vec3<double> & dataPoint)
{
    std::uint32_t clusterId = 0;
    double minDistance = std::numeric_limits<double>::max();
    for(std::uint32_t i = 0; i < gravityPoints.size(); ++i)
    {
        double distance = dataPoint.DistTo(gravityPoints[i]);
        if(distance < minDistance)
        {
            minDistance = distance;
            clusterId = i;
        }
    }

    vectorOfClusters[clusterId].emplace_back(dataPoint);
}

void recalculateGravityPointPosition(Vec3<double> & p, const std::vector<Vec3<double>> & cluster)
{
    if(cluster.size() == 0)
        return;
    
    Vec3<double> averageClusterPosition(0.0);
    for(const auto & p : cluster)
        averageClusterPosition += p;

    p = averageClusterPosition / cluster.size();
}

std::vector<std::vector<Vec3<double>>> calculateClustersKMeans(std::vector<Vec3<double>> & dataPoints, std::uint32_t kClusters, std::vector<Vec3<double>> & gravityPoints, std::vector<std::vector<Vec3<double>>> & vectorOfClusters)
{
    std::vector<std::vector<Vec3<double>>> newVectorOfClusters(kClusters, std::vector<Vec3<double>>());

    std::cout << "Assign each data point to it's corresponding cluster...\n";
    //Assign each data point to it's corresponding cluster
    for(auto & p : dataPoints)
        assignDataPointToCluster(newVectorOfClusters, gravityPoints, p);

    std::cout << "Recalculate the position of each gravity point...\n";
    //Recalculate the position of each gravity point
    for(std::uint32_t i = 0; i < gravityPoints.size(); ++i)
        recalculateGravityPointPosition(gravityPoints[i], newVectorOfClusters[i]);

    std::cout << "\n\n";
    std::cout << "Recalculated Gravity Points: ";
    for(const auto & p : gravityPoints)
        std::cout << p << " | ";
    
    std::cout << "\n\n\n";
    
    std::cout << "Sort and compare the new vectorOfClusters with the old one...\n";
    //Sort and compare the new vectorOfClusters with the old one
    for(std::uint32_t i = 0; i < newVectorOfClusters.size(); ++i)
        std::sort(newVectorOfClusters[i].begin(), newVectorOfClusters[i].end());

    if(newVectorOfClusters != vectorOfClusters)
    {
        std::cout << "Not equal, recalculando clusters..." << std::endl;
        vectorOfClusters.clear();
        return calculateClustersKMeans(dataPoints, kClusters, gravityPoints, newVectorOfClusters);   
    }
    
    std::cout << "Fim..." << std::endl;
    return newVectorOfClusters;
}

std::vector<std::vector<Vec3<double>>> getClustersKMeans(std::vector<Vec3<double>> & dataPoints, std::uint32_t kClusters)
{
    //Get kClusters random gravity points...
    std::vector<Vec3<double>> gravityPoints = getRandomGravityPoints(dataPoints, kClusters);
    std::cout << "Gravity Points: ";
    for(const auto & p : gravityPoints)
        std::cout << p << " | ";

    std::cout << "\n\n\n";
    //Create our vectorOfClusters
    std::vector<std::vector<Vec3<double>>> vectorOfClusters(kClusters, std::vector<Vec3<double>>());

    return calculateClustersKMeans(dataPoints, kClusters, gravityPoints, vectorOfClusters);
}

int main()
{
    /*for(int i = 0; i < 99; i++)
        std::cout << getRandomNumber<int>(0,2) << ' ';*/
    Vec3<double> a(1.0, 1.0, 0.0);
    Vec3<double> b(2.0, 3.0, 0.0);
    //std::cout << a.DistTo(b) << std::endl;
    //return 0;
    Vec3<double> c(1.5, 1.5, 0.0);

    Vec3<double> d(10.0, 10.0, 0.0);
    Vec3<double> e(11.0, 11.0, 0.0);
    Vec3<double> f(10.5, 10.5, 0.0);

    std::vector<Vec3<double> > pontos = {a,b,c,d,e,f};
    std::vector<std::vector<Vec3<double>>> resultado = getClustersKMeans(pontos, 2);
    //std::vector<Vec3<double> > pontosGravidade = getRandomGravityPoints(pontos, 7);
    std::cout << "Clusters..\n\n";
    for(const auto & cluster : resultado)
    {
        std::cout << "Cluster..\n";
        for(const auto & c : cluster)
        {
            std::cout << c << " | ";
        }
        std::cout << "\n\n";
    }
    //calculate_k_means(pontos, 2);
    return 0;
    /*std::cout << "Pontos: ";
    for(const auto & p : pontos)
        std::cout << p << " | ";

    std::cout << "\n\n";

    std::cout << "Gravity: ";
    for(const auto & p : pontosGravidade)
        std::cout << p << " | ";
    */
}





/*

Deve receber um vetor de pontos
E um número de k grupos

com isso, escolher k pontos aleatorios
para serem os pontos de gravidade
e colocalos em um vetor de pontos de gravidade

após isso, criar um vetor contendo k vetores de Vec3
será um vetor de clusters..

com isso, podemos começar as iteracoes:
1. para cada ponto, calcular
a distancia para cada ponto de gravidade
a menor distancia vc coloca o ponto
iterado no vetor correspondente

2. calcular a média de cada cluster
e atribuir esse local para o ponto de 
gravidade correspondente do vetor

3. sort cada cluster

4. comparar cada cluster novo com seu antigo
caso exista discrepancia, calcular tudo de novo
caso contrário, finalizar calculo e retornar o
vetor de clusters


*/