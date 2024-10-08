// Make sure to include these imports:
import { GoogleGenerativeAI } from "@google/generative-ai";

// Define palavras padrao caso não receba um prompt
const palavrasPadrao = [
"canto", "falar", "linda", "morar", "pouco", "verde", "terra", "carro", "feliz", "amigo",
"jogar", "vento", "praia", "corpo", "longe", "curta", "brava", "banho", "grato", "ponto",
"certo", "custo", "calmo", "nuvem", "caixa", "porta", "rampa", "limpo", "ostra", "traje",
"roupa", "trigo", "fruta", "pedra", "justo", "longo", "fosco", "folha", "nevoa", "vento",
"molho", "leito", "lucro", "matiz", "haste", "flora", "troca", "carne", "fenda", "peito",
"vapor", "vazio", "truco", "visto", "ferro", "livro", "prato", "brisa", "nobre", "talho",
"meiga", "prego", "navio", "manga", "farda", "feira", "meigo", "regra", "sagaz", "ritmo",
"tempo", "barra", "areia", "chuva", "tarde", "remar", "queda", "monta", "tenue", "tocar",
"limpa", "cegar", "rosca", "norte", "lugar", "plano", "leque", "vinho", "fauna", "suave",
"haste", "traje", "toque", "monte", "nuvem", "fugaz", "haste", "breve", "firma", "cinto", 
"moral", "amiga", "campo", "banco", "fardo", "falsa", "briga", "coisa", "certo", "chato", 
"claro", "drama", "densa", "escol", "fator", "feita", "forma", "gasto", "graca", "homem", 
"igual", "jovem", "junho", "lavar", "lugar", "legal", "manha", "mundo", "noite", "final",
"nacao", "papel", "parte", "prato", "perto", "quase", "rapaz", "regra", "ruido", "sorte", 
"tempo", "termo", "uniao", "vazio", "valor", "verde", "xisto", "zebra", 
];

// Salva as palavras do array palavrasPadrao no armazenamento local até que seja subscrito 
localStorage.setItem('palavrasGeradas', JSON.stringify(palavrasPadrao));

const API_KEY = "AIzaSyDYrb194r1yd0cwlWvlgx7GbqPoKz9_H80";
const genAI = new GoogleGenerativeAI(API_KEY);
const model = genAI.getGenerativeModel({ model: "gemini-1.5-flash" });

const resultadoGeracaoRuim = document.querySelector("#resultadoGeracaoRuim")
const resultadoGeracaoBom = document.querySelector("#resultadoGeracaoBom")

async function gerarPalavras(prompt) {

    const consulta = [
        {text: "Gere até 100 palavras em português com exatamente 5 letras separadas por vírgula. Apenas as palavras com 5 letras de A a Z, caso uma palavra contenha 'ç' ou acentuação substitua por caracter normal por exemplor maçãs seria macas, se uma palavra não tiver 5 letras remova, de maneira alguma uma palavra pode ter menos ou mais que 5 letras, tente gerar o máximo de palavras possivel, se a palavra não faz sentido remova. O tema é definido pelo usuário"},
        {text: "input: comida"},
        {text: "output: aipim, amora, araca, arroz, aveia, avelã, bacon, bauru, cacau, caqui, carne, chopp, cidra, clara, couve, cravo, crepe, curau, curry, glace, jambo, jatai, leite, licor, limão, lombo, louro, mamão, manga, melao, menta, milho, nozes, orobo, pequi, pinha, pirão, pizza, pudim, quibe, ração, salsa, saquê, sonho, sufle, sushi, torta, trigo, trufa, vagem, vinho, vodca"},
        {text: `input: o tema é palavras relacionadas a ${prompt} com 5 letras apenas`},
        {text: "output: "},
      ];

    try {
        const result = await model.generateContent(consulta);
        const response = await result.response;
        const text = response.text();

        // Limpar o texto e retornar o array de palavras
        return limparTexto(text);
    } catch (error) {
        console.error("Erro ao gerar palavras:", error);
        resultadoGeracaoRuim.textContent = "Ocorreu um erro ao gerar as palavras. Por favor, tente novamente.";
        return [];
    }
}

    function limparTexto(texto) {
    // Separar a string em um array usando a vírgula como separador e remover espaços em branco
    const palavras = texto.split(', ').map(palavra => palavra.trim());

    // Expressão regular para verificar caracteres especiais
    const regex = /[^a-zA-Zà-úÀ-Ú ]/g;

    // Normalizar todos os nomes de uma vez e filtrar as palavras válidas
    return palavras.map(palavra => palavra.normalize('NFD').replace(/[\u0300-\u036f]/g, "")).filter(palavra => !regex.test(palavra) && palavra.length === 5);
    }

    function desativaBotao() {

    const botaoPlay = document.querySelector("#botao-play")

    botaoPlay.disabled = true

    botaoPlay.innerText = "Gerando palavras..."

    }



  function ativaBotao() {

    const botaoPlay = document.querySelector("#botao-play")

    botaoPlay.disabled = false

    botaoPlay.innerText = "Jogar"

    }

    // Seleciona o botão play
    const botao = document.getElementById('botao-play');

    // Adiciona o evento de clique ao botão play
    botao.onclick = function() {
      // Redireciona para a outra página
      window.location.href = "tabela.html";
    };


document.querySelector("#Confirmar_prompt").addEventListener("click", async () => {
    desativaBotao();
    const prompt = document.querySelector("#input_prompt").value;

    // Exibir mensagem de carregamento
    // resultadoConsulta.textContent = "Gerando palavras...";

    const palavras = await gerarPalavras(prompt);

    if (palavras.length > 0) {
        // resultadoConsulta.textContent = 'Gerado!';

        // Armazenar as palavras no localStorage como um JSON
        localStorage.setItem('palavrasGeradas', JSON.stringify(palavras));
        resultadoGeracaoBom.textContent = `Jogo sobre o tema ${prompt} criado`;
        ativaBotao();
    } else {
        resultadoGeracaoRuim.textContent = "Nenhuma palavra encontrada.";
        ativaBotao();
    }
});
