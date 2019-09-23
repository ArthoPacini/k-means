#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include "Vec3.h"

namespace art
{
    class Benchmark
    {
        private:
            std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long, std::ratio<1, 1000000000> > > comecoDoBenchmark;
            std::string mensagemAntes;
            std::string mensagemDepois;
        public:
            Benchmark(std::string m1 = "", std::string m2 = "")
            {
                comecoDoBenchmark = std::chrono::steady_clock::now();
                mensagemAntes = m1;
                mensagemDepois = m2;
            }

            ~Benchmark()
            {
                auto finalDoBenchmark = std::chrono::steady_clock::now();
                auto tempoDeExecucao = finalDoBenchmark - comecoDoBenchmark;
                std::cout << mensagemAntes << std::chrono::duration <double, std::milli> (tempoDeExecucao).count() << " ms " << mensagemDepois << "\n";
            }
    };
}

template <typename T>
T getRandomNumber(const T min = std::numeric_limits<T>::min(), const T max = std::numeric_limits<T>::max())
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<T> random_distribution(min, max);
    return random_distribution(mt);
}

class KMeans
{
    private:
        std::vector<Vec3<double>> dataPoints;
        std::uint32_t kClusters;
        std::vector<std::vector<Vec3<double>>> result;
        bool alreadyComputed;
    public:
        KMeans(const std::vector<Vec3<double>> data, const std::uint32_t k, const bool startComputeRightAway = false) : dataPoints(data), kClusters(k) 
        {
            alreadyComputed = false;
            if(startComputeRightAway)
                result = getClustersKMeans(dataPoints, kClusters);
        }

        std::vector<std::vector<Vec3<double>>> getResult()
        {
            //If already computed, return results
            if(alreadyComputed)
                return result;

            //Otherwise, compute and return results
            result = getClustersKMeans(dataPoints, kClusters);
            return result;
        }

    private:

        /*template <typename T>
        T getRandomNumber(const T min = std::numeric_limits<T>::min(), const T max = std::numeric_limits<T>::max())
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<T> random_distribution(min, max);
            return random_distribution(mt);
        }*/

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

            //Assign each data point to it's corresponding cluster //MULTITHREAD THAT BITCH
            for(auto & p : dataPoints)
                assignDataPointToCluster(newVectorOfClusters, gravityPoints, p);

            //Recalculate the position of each gravity point //MULTITHREAD THAT BITCH
            for(std::uint32_t i = 0; i < gravityPoints.size(); ++i)
                recalculateGravityPointPosition(gravityPoints[i], newVectorOfClusters[i]);
        
            //Sort and compare the new vectorOfClusters with the old one //MULTITHREAD THAT BITCH
            for(std::uint32_t i = 0; i < newVectorOfClusters.size(); ++i)
                std::sort(newVectorOfClusters[i].begin(), newVectorOfClusters[i].end());

            if(newVectorOfClusters != vectorOfClusters) //MULTITHREAD THAT BITCH
            {
                vectorOfClusters.clear();
                return calculateClustersKMeans(dataPoints, kClusters, gravityPoints, newVectorOfClusters);   
            }
            
            alreadyComputed = true;
            return newVectorOfClusters;
        }

        std::vector<std::vector<Vec3<double>>> getClustersKMeans(std::vector<Vec3<double>> & dataPoints, std::uint32_t kClusters)
        {
            //Get kClusters random gravity points...
            std::vector<Vec3<double>> gravityPoints = getRandomGravityPoints(dataPoints, kClusters);

            //Create our vectorOfClusters
            std::vector<std::vector<Vec3<double>>> vectorOfClusters(kClusters, std::vector<Vec3<double>>());
            return calculateClustersKMeans(dataPoints, kClusters, gravityPoints, vectorOfClusters);
        }
};

int main()
{
    std::vector<Vec3<double>> pontos;
    pontos.reserve(1000);
    for(std::uint32_t i = 0 ; i < 1000; ++i)
        pontos.emplace_back(Vec3<double>(getRandomNumber<double>(1.0,1000.0)));

    std::cout << "Comecando a calcular.." <<std::endl;
    KMeans calculo(pontos, 2, true);
    std::vector<std::vector<Vec3<double>>> resultado = calculo.getResult();

    for(std::uint32_t i = 0; i < resultado.size(); ++i)
        std::cout << "\nCluster " << i+1 << " contains " << resultado[i].size() << " objects...";
    
    return 0;
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
    
    return 0;

}





/*

-->Chamada da funcao
Deve receber um vetor de pontos (dataPoints)
E um número de k grupos (kClusters)

-->Pre inicio da funcao
com isso, escolher k pontos aleatorios
para serem os pontos de gravidade
e colocalos em um vetor de pontos de gravidade

após isso, criar um vetor contendo k vetores de Vec3
será um vetor de clusters..


-->Funcao recursiva
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