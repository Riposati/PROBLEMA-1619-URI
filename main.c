#include <stdio.h>
#include <stdlib.h>

#define janeiro 31
#define fevereiroNaoBissexto 28
#define fevereiroBissexto 29
#define marco 31
#define abril 30
#define maio 31
#define junho 30
#define julho 31
#define agosto 31
#define setembro 30
#define outubro 31
#define novembro 30
#define dezembro 31

int retornaSeEBissexto(int ano){

    int flag = 0;

    if(ano % 4 == 0 || ano % 400 == 0 && (ano % 100 != 0)){

        flag = 1;
    }

    return flag;
}

int assumeValoresMes(int i, int ano){

    if(i==1){

        i = janeiro;
    }

    if(i==2){

        int flagVerificaBissexto = retornaSeEBissexto(ano);

        if(flagVerificaBissexto==1){

            i = fevereiroBissexto;
        }else{

            i = fevereiroNaoBissexto;
        }
    }

    if(i==3)
        i = marco;

    if(i==4)
        i = abril;

    if(i==5)
        i = maio;

    if(i==6)
        i = junho;

    if(i==7)
        i = julho;

    if(i==8)
        i = agosto;

    if(i==9)
        i = setembro;

    if(i==10)
        i = outubro;

    if(i==11)
        i = novembro;

    if(i==12)
        i = dezembro;
    
    return i;
}

int diferencaAnosIguaisMesesIguais(int anoFinal,int anoInicial,int mesFinal,int mesInicial,int diaFinal,int diaInicial){

    int total = 0;

    total = diaFinal - diaInicial;

    return total;
}

int diferencaAnosIguaisMesesDiferentes(int anoFinal,int anoInicial,int mesFinal,int mesInicial,int diaFinal,int diaInicial){

    int total=0,totalDiferencaDiasEntreMeses=0,qtdDiasFaltamParaFimMesInicial=0;
    int i=1,diferencaMeses;

    if(mesFinal > mesInicial){ /// serve para trocar a ordem das datas caso a primeira venha maior

        int aux2 = mesFinal;
        int aux3 = diaFinal;

        mesFinal = mesInicial;
        diaFinal = diaInicial;

        diaInicial = aux3;
        mesInicial = aux2;
    }

    diferencaMeses = mesFinal + 1;

    while(diferencaMeses < mesInicial){ /// acha a qtd de dias entre o mes inicial e o final

        i = diferencaMeses;
        totalDiferencaDiasEntreMeses += assumeValoresMes(i,anoFinal);
        diferencaMeses++;
    }

    qtdDiasFaltamParaFimMesInicial = assumeValoresMes(mesFinal,anoFinal) - diaFinal;

    total = qtdDiasFaltamParaFimMesInicial + totalDiferencaDiasEntreMeses + diaInicial;

    return total;
}

int analisaDataFinal(int anoFinal,int mesFinal,int diaFinal){

    int total=0,totalDiferencaDiasEntreMeses=0,qtdDiasFaltamParaFimMesInicial=0;
    int diferencaMeses,sum=0;

    /// parte da data final, quantidade de dias que faltam pro fim do mes - tam mes +
    /// dias até o final deste ano e verificar se é bissexto

    int tamMes = assumeValoresMes(mesFinal,anoFinal);

    total = abs(tamMes - diaFinal);

    mesFinal +=1;

    while(mesFinal <= 12){

        sum +=assumeValoresMes(mesFinal,anoFinal);

        mesFinal++;
    }

    total += sum;

    return total;
}

int analisaDataInicial(int anoInicial,int mesInicial,int diaInicial){

    int total=0,totalDiferencaDiasEntreMeses=0,qtdDiasFaltamParaFimMesInicial=0;
    int i=1,diferencaMeses,sum=0;

    /// parte da data inicial, quantidade de dias passados já no ano + qtd de dias já passados no mes que quero verificando se é bissexto
    /// porque fevereiro bissexto tem 29 dias

    while(i < mesInicial){

        sum += assumeValoresMes(i,anoInicial);

        i++;
    }

    total = sum + diaInicial;

    return total;
}

int analisaAnosIntervalo(int anoFinal,int anoInicial){

    int total=0,totalDiferencaDiasEntreMeses=0,qtdDiasFaltamParaFimMesInicial=0;
    int i=0,diferencaMeses,sum=0;

    /// pega o intervalo de anos e faz o somatorio

    anoFinal +=1;

    while(anoFinal < anoInicial){

        int aux = retornaSeEBissexto(anoFinal);

        if(aux==1)

            sum += 366;

        else
            sum +=365;

        anoFinal++;
    }

    return sum;
}

int main()
{
    int anoFinal;
    int anoInicial;
    int mesFinal;
    int mesInicial;
    int diaFinal;
    int diaInicial;
    char traco;
    int resposta=0,qtdTestes;

    scanf("%d",&qtdTestes);

    while(qtdTestes--){

        scanf("%d %c %d %c %d",&anoFinal,&traco,&mesFinal,&traco,&diaFinal);
        scanf("%d %c %d %c %d",&anoInicial,&traco,&mesInicial,&traco,&diaInicial);

        if(diaFinal==diaInicial && anoFinal==anoInicial && mesFinal==mesInicial){ /// tudo igual , OKS

            resposta = 0;
        }

        if(anoFinal==anoInicial && mesFinal==mesInicial){ /// anos e mes iguais , OKS

            resposta = diferencaAnosIguaisMesesIguais(anoFinal,anoInicial,mesFinal,mesInicial,diaFinal,diaInicial);
        }

        if(anoFinal==anoInicial && mesFinal!=mesInicial){ /// ano igual e meses diferentes , OKS

            resposta = diferencaAnosIguaisMesesDiferentes(anoFinal,anoInicial,mesFinal,mesInicial,diaFinal,diaInicial);
        }

        if(anoFinal!=anoInicial){ /// anos diferentes e meses diferentes

            if(anoFinal > anoInicial){ /// serve para trocar a ordem das datas caso a primeira venha maior
                int aux2 = mesFinal;
                int aux3 = diaFinal;
                int aux = anoFinal;

                mesFinal = mesInicial;
                diaFinal = diaInicial;
                anoFinal = anoInicial;

                diaInicial = aux3;
                mesInicial = aux2;
                anoInicial = aux;
            }
            
            int a = analisaDataFinal(anoFinal,mesFinal,diaFinal);
            int b = analisaDataInicial(anoInicial,mesInicial,diaInicial);
            int c = analisaAnosIntervalo(anoFinal,anoInicial);

            resposta = a + b + c;
        }

        printf("%d\n",abs(resposta));
        resposta = 0;
    }

    return 0;
}
