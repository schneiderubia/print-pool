#include <random>
#include <iostream>
#include "process.h"
#include "log.h"

Process::Process(pid_t pid) : pid(pid) {

}

void Process::start(Pool &pool) {

    thread = std::thread(&simulate, std::ref(*this), std::ref(pool));
    thread.detach();
}

void Process::simulate(const Process &process, Pool &pool) {

    int n = randomNumber(5, 10);
    Log::getInstance().print(std::format("Processo {} enviando {} documentos", process.pid, n));
    for(int i = 0; i < n; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(randomNumber(0, 5000)));
        pool.receiveFile(process.pid, randomFileName(), randomNumber(1, 5));
    }
}

std::string Process::randomFileName() {
    static std::vector<std::string> files = {
            "documento.txt",
            "foto.jpg",
            "relatorio.pdf",
            "dados_2024.xlsx",
            "projeto_code.cpp",
            "apresentacao.pptx",
            "design_logo.psd",
            "musica.mp3",
            "video_editado.mp4",
            "script_automacao.py",
            "configuracao.yaml",
            "modelo_template.docx",
            "backup_arquivo.zip",
            "tabela_info.csv",
            "diagrama_fluxo.vsdx",
            "config_sys.ini",
            "app_instalador.exe",
            "index.html",
            "estilos.css",
            "java_programa.java",
            "imagem_fundo.png",
            "relatorio_analise.docx",
            "audio_gravacao.wav",
            "video_apresentacao.mov",
            "planilha_financeira.ods",
            "script_processamento.r",
            "documento_referencia.odt",
            "arquivo_config.txt",
            "projeto_website.html",
            "lista_compras.md",
            "dicionario_termos.json",
            "logs_sistema.log",
            "backup_db.sql",
            "grafico_vendas.svg",
            "template_email.eml",
            "imagem_projeto.bmp",
            "video_tutorial.avi",
            "modelo_pesquisa.tex",
            "apresentacao_slide.odp",
            "relatorio_execucao.xls",
            "scripts_utilitarios.sh",
            "arquivo_dados.bin",
            "tabela_preco.tsv",
            "sistema_instalador.pkg",
            "documento_reuniao.rtf",
            "audio_musical.aac",
            "video_suporte.mp4",
            "imagem_capitulo.gif",
            "relatorio_finalizado.pdf",
            "config_servidor.conf",
            "projeto_backup.tar.gz"
    };
    return files[randomNumber(0, static_cast<int>(files.size()) - 1)];
}

int Process::randomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}
