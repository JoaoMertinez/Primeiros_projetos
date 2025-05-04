import cherrypy
from classes.especie import Especie # ou from classes.especie import0 *

class PaginaEspecie():
    #topo = open("HTML/telaP.html").read()
    #rodape = open("html/rodape.html").read()

    @cherrypy.expose()
    def index(self):
        return self.montaFormulario()

    def montaFormulario(self, pNome='', pEmail='', pCpf='', pEnd_rua='', pEnd_num=0, pCidade='', pGenero='', pCategoria=0,pCurso1=0, pCurso2=0, pCurso3=0, pCurso4=0,pCamissa=''):
        str = self
        str = '''
                    <form name="FormCadastro" action="gravarEspecie" method="post">  
                    <!DOCTYPE html>
                    <html lang="en">
                    <head>
                        <meta charset="UTF-8">
                        <meta name="viewport" content="width=device-width, initial-scale=1.0">
                        <link rel="stylesheet" href="/CSS/cadastro.css">
                        <title>Document</title>
                    </head>
                    <body style="background:url(../Fotos/fundoo.png) ; flex-direction: column;">
                        <div class="conteiner grupo">
                            <div class="card"> 
                                <h1 class="title" id="title">CADASTRO INFOESTE</h1>
                                <p class="title">Complete suas informações:</p>
                    
                                <div class="label-float">
                                    <div>
                                        <H4>NOME COMPLETO: </H4>
                                        <input type="text" name="txtNome" id="txtNome" class="input-label" placeholder="Digite seu nome" required value="%s">
                                    </div>
                                </div>
                    
                                <div  class="label-float">
                                  <H4>E-MAIL:</H4>
                                    <input type="text" name="txtEmail" id="txtEmail" class="input-label"  value="%s" placeholder="Digite seu email" required>
                                </div>
                    
                                <div  class="label-float">
                                    <H4>CPF:</H4>
                                    <input type="text" id="txtCpf" name="txtCpf" maxlength="14" class="input-label" value="%s" placeholder="000.000.000-00" required>
                                </div>
                    
                                <div  class="label-float">
                                  <H4>ENDEREÇO: </H4>
                                    <input type="text" id="txtEnd_rua" name="txtEnd_rua" class="input-label" value="%s"placeholder="Digite o nome da sua rua:" required>
                                </div>
                    
                                <div  class="label-float">
                                    <H4>NUMERO: </H4>
                                      <input type="text" id="txtEnd_num" name="txtEnd_num" class="input-label" value="%d" placeholder="Digite o numero e complemento:" required>
                                </div>
                    
                                <div  class="label-float">
                                    <H4>CIDADE:</H4>
                                    <input type="text" id="txtCidade" name="txtCidade" class="input-label" value="%s" placeholder="Digite a cidade" required>
                                </div>
                                <!--GENERO-->
                                <div class="label-float">
                                    <div class="radio-container">
                                        <H3>GÊNERO</H3>
                                        <ul>
                                            <li>F - FEMININO</li>
                                            <li>M - MASCULINO</li>
                                            <li>O - OUTROS</li>
                                            <li>PNI - PREFIRO NÃO INFORMAR</li>
                                        </ul>
                                    <div  class="label-float">
                                        <input type="text" id="txtGenero" name="txtGenero" class="input-label" value="%s" placeholder="Digite (F,M,O ou PNI)" required>
                                    </div>   
                                         
                                      </div>
                                </div> <!--GENERO-->
                    
                                <div class="label-float"> <!----Categoria-->
                                   <h3>CATEGORIA DO PARTICIPANTE</h3>
                                   <h4>Digite uma opção</h4>
                                    <ul>
                                        <li>1- Alunos ETEC´s</li>
                                        <li>2- Alunos da Graduação Presencial - FIPP</li>
                                        <li>3- BSU - Business School Unoeste</li>
                                        <li>4- Demais Participantes</li>
                                        <li>5- Egressos da FIPP</li>
                                        <li>6- Professores e Funcionários da FIPP</li>
                                    </ul>
                                    <div  class="label-float">
                                        <input type="text" id="txtCategoria" name="txtCategoria" class="input-label" value="%d" placeholder="Digite a categoria" required>
                                    </div> 
                                </div><!----Categoria-->
                            </div>
                        </div>
                        <div>
                         <!----CURSOS-->
                             <div class="label-float">
                                   <h2 id="center">SELECIONE OS CURSOS QUE DESEJA PARTICIPAR</h2>
                                        <div class="checkbox-container">
                                            <div class="checkbox-scroll">
                    
                                                <ul style="text-align: left;">
                                                     <li>1- MC01 - Criatividade e Geração de ideias</li>
                                                     <li>2- MC02 - Node.JS com testes unitários e Prisma</li>
                                                     <li>3- MC03 - Introdução a Maratona de Programação</li>
                                                     <li>4- MC04 - Empreendedorismo Tecnológico</li>
                                                     <li>5- MC05 - O Essencial de GIT e GitHub</li>
                                                     <li>6- MC06 - Marketing Digital</li>
                                                     <li>7- MC07 - Intensivo ReactJS e Typescript</li>
                                                     <li>8- MC10 - Scrum: Metodologia Ágil</li>
                                                     <li>9- MC11 - Introdução ao Agile Thinking</li>
                                                     <li>10- MC12 - Workshop sobre testes de capacidade com JMETER, K6 e GRAFANA</li>
                                                     <li>11- MC13 - Workshop Introdução a Qualidade de Software, automação, alguns frameworks, cases e aplicações</li>
                                                     <li>12- MC14 - Introdução ao UX Design</li>
                                                     <li>13- MC15 - Power BI</li>
                                                     <li>14- MC16 - Introdução a Segurança da Informação com Linux</li>
                                                     <li>15- MC17 - Práticas de Eletrônica Digital</li>
                                                     <li>16- MC18 - Introdução a APIs REST com Node.js e ferramentas de testes automatizados</li>
                                                     <li>17- MC19 - Introdução ao Github</li>
                                                     <li>18- ET01 - Blender 3D</li>
                                                     <li>19- ET03 - Introdução ao Unity 3D</li>
                                                     <li>20- ET07 - Produção de Conteúdo para o Instagram</li>
                                                     <li>21- ET09 - Desenvolvimento Web para Iniciantes e utilização de frameworks CSS</li>
                                                     <li>22- 16ª Festa Linux para Principiantes</li>
                                                     <li>23- 16ª Maratona de Programação da Faculdade de Informática de Presidente Prudente</li>
                                                 </ul>
                                                <br>
                                                <br>
                                                <h4 for="selectedOptions">Digite os número da opção desejada:</h4>
                                                <input type="text" id="txtCurso1" name="txtCurso1" placeholder="Ex: 1"  value="%d">
                                                <input type="text" id="txtCurso2" name="txtCurso2" placeholder="Ex: 2"  value="%d">
                                                <input type="text" id="txtCurso3" name="txtCurso3" placeholder="Ex: 3"  value="%d">
                                                <input type="text" id="txtCurso4" name="txtCurso4" placeholder="Ex: 4"  value="%d">
                                                <br>
                                                
                                                </div>
                                            </div>
                                        </div>
                             </div>
                        </div>
                        <br>
                        <br>
                        <div class="alinhamento">
                            <div class="imagem">
                                <img src="/Fotos/camisafrente.png" alt="Imagem Base">
                                <img src="/Fotos/camisacostas.png" alt="Imagem Hover" class="imagem-hover">
                            </div>
                           <br>
                    
                            <div class="espacamento">
                                <label class="camisas"> Digite o tamanho da sua camisa: </label>
                                <h4>TAMANHOS</h4>
                                <ul>
                                    <li>MB- BABY LOOK</li>
                                    <li>GB- BABY LOOK</li>
                                    <li>PP- CAMISA</li>
                                    <li>P- CAMISA</li>
                                    <li>M- CAMISA</li>
                                    <li>G- CAMISA</li>
                                    <li>GG-CAMISA</li>
                                </ul>
                                <div  class="label-float">
                                        <input type="text" id="txtCamissa" name="txtCamissa" class="input-label" value="%s" placeholder="Digite (PB,GB,PP,P,M,G ou GG)" required>
                                    </div> 
                            </div>
                            <div class="cont label-float">
                                <script>
                                        <a href="telaP.html" class="botao" id="botao-cadastrar" type="submit">CADASTRAR</a>
                                </script>
                            </div>
                        </div>
                    </body>
                    </html>   
                    <input type="submit" id="btnGravar" name="btnGravar" value="Gravar"/>
                     </form>
                 ''' % (pNome, pEmail, pCpf, pEnd_rua,pEnd_num, pCidade, pGenero, pCategoria, pCurso1, pCurso2, pCurso3, pCurso4,pCamissa)

        str += self.montaTabela()
        #str += self.rodape

        return str


    def montaTabela(self):
        html = '''<table style="background:white; border: 4px solid black; text-align:center;" >
                     <tr>
                        <th>Nome</th>
                        <th>Email</th>
                        <th>CPF</th>
                        <th>Rua</th>
                        <th>Numero</th>
                        <th>Cidade</th>
                        <th>Genero</th>
                        <th>Categoria</th>
                        <th>Curso1</th>
                        <th>Curso2</th>
                        <th>Curso3</th>
                        <th>Curso4</th>
                        <th>Tamanho</th>
                        <th>Ações</th>
                     </tr> '''
        # buscar os dados do banco de dados
        objEspecie = Especie() # criamos um objeto do tipo Especie
        dados = objEspecie.obterEspecies() # será criada uma lista com o resultado o SQL
        for linha in dados:
            html += ''' <tr style="text-align:center;">
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td style="text-align:center;">
                              <a href="excluirEspecie?cpfCad=%s">[Excluir]</a>
                              <a href="alterarEspecie?cpfCad=%s">[Alterar]</a>
                           </td>
                        </tr> ''' % (linha['cad_nome'], linha['cad_email'],linha['cad_cpf'], linha['cad_end_rua'], linha['cad_end_num'], linha['cad_cidade'], linha['cad_genero'], linha['cad_categoria'], linha['cad_curso1'], linha['cad_curso2'], linha['cad_curso3'], linha['cad_curso4'], linha['cad_camissa'],linha['cad_cpf'],linha['cad_cpf'])
        html +=''' </table> <br> <br>'''
        return html

    @cherrypy.expose()
    def gravarEspecie(self, txtNome, txtEmail, txtCpf, txtEnd_rua, txtEnd_num, txtCidade, txtGenero, txtCategoria, txtCurso1, txtCurso2, txtCurso3, txtCurso4, txtCamissa,btnGravar):  # vai ser chamado quando clicar no botão
        if len(txtNome) > 0:
            # fazer os procedimentos para gravar
            objEspecie = Especie()
            objEspecie.set_nome(txtNome)
            objEspecie.set_email(txtEmail)
            objEspecie.set_cpf(txtCpf)
            objEspecie.set_end_rua(txtEnd_rua)
            objEspecie.set_end_num(txtEnd_num)
            objEspecie.set_cidade(txtCidade)
            objEspecie.set_genero(txtGenero)
            objEspecie.set_categoria(txtCategoria)
            # objEspecie.set_foto(txtFoto)
            objEspecie.set_curso1(txtCurso1)
            objEspecie.set_curso2(txtCurso2)
            objEspecie.set_curso3(txtCurso3)
            objEspecie.set_curso4(txtCurso4)
            objEspecie.set_camissa(txtCamissa)

            retorno = 0

            retorno = objEspecie.gravar()

            if retorno > 0:
                return '''
                        <script>
                           alert("%s foi Cadastrada(o) com sucesso!!")
                           window.location.href = "/"
                        </script>
                       ''' % (txtNome)

    #
    # @cherrypy.expose()
    # def excluirEspecie(self,idEsp):
    #     objEspecie = Especie()
    #     objEspecie.set_id(int(idEsp))
    #     if objEspecie.excluir() > 0: # informa se conseguiu excluir ou não
    #         raise cherrypy.HTTPRedirect('/rotaEspecie') # para atualizar a página após a exclusão (tipo reload)
    #     else:
    #         return '''
    #         <h2>Não foi possível excluir a espécie!!</h2>
    #         [<a href="/rotaEspecie">Voltar</a>]
    #         '''

    @cherrypy.expose()
    def excluirEspecie(self, cpfCad):
        objEspecie = Especie()
        objEspecie.set_cpf(cpfCad)
        if objEspecie.excluir() > 0:  # informa se conseguiu excluir ou não
            raise cherrypy.HTTPRedirect('/rotaEspecie')  # para atualizar a página após a exclusão (tipo reload)
        else:
            return '''
             <h2>Não foi possível excluir a espécie!!</h2>
             [<a href="/rotaEspecie">Voltar</a>]
             '''

    @cherrypy.expose()
    def alterarEspecie(self, cpfCad):
        objEspecie = Especie()
        # buscar no banco a espécie que foi informada no parâmetro
        dadosEspecieSelec = objEspecie.obterEspecie(cpfCad)
        # chamar o método para montar o formulário com os dados da espécie selecionada na tabela e carregar nos elementos <input> do formulário
        return self.montaFormulario(dadosEspecieSelec[0]['cad_nome'],
                                    dadosEspecieSelec[0]['cad_email'],
                                    dadosEspecieSelec[0]['cad_cpf'],
                                    dadosEspecieSelec[0]['cad_end_rua'],
                                    dadosEspecieSelec[0]['cad_end_num'],
                                    dadosEspecieSelec[0]['cad_cidade'],
                                    dadosEspecieSelec[0]['cad_genero'],
                                    dadosEspecieSelec[0]['cad_categoria'],
                                    dadosEspecieSelec[0]['cad_curso1'],
                                    dadosEspecieSelec[0]['cad_curso2'],
                                    dadosEspecieSelec[0]['cad_curso3'],
                                    dadosEspecieSelec[0]['cad_curso4'],
                                    dadosEspecieSelec[0]['cad_camissa'])


    # @cherrypy.expose()
    # def alterarEspecie(self,idEsp):
    #     objEspecie = Especie()
    #     # buscar no banco a espécie que foi informada no parâmetro
    #     dadosEspecieSelec = objEspecie.obterEspecie(idEsp)
    #     # chamar o método para montar o formulário com os dados da espécie selecionada na tabela e carregar nos elementos <input> do formulário
    #     return self.montaFormulario(dadosEspecieSelec[0]['esp_id'],
    #                                 dadosEspecieSelec[0]['esp_descricao'],
    #                                 dadosEspecieSelec[0]['esp_origem'])