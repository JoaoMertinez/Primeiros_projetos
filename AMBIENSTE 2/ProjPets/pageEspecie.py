import cherrypy
from classes.especie import Especie # ou from classes.especie import0 *

class PaginaEspecie():
    topo = open("html/cabecalho.html").read()
    rodape = open("html/rodape.html").read()

    @cherrypy.expose()
    def index(self):
        return self.montaFormulario()

    def montaFormulario(self, pId=0, pDescr='', pOrigem=''):
        str = self.topo
        str += '''
                <h2>Espécies de Animais</h2>
                <form name="FormCadastro" action="gravarEspecie" method="post">
                <p>
                 <input type="hidden" id="txtId" name="txtId" value="%s"/>
                 
                 <label for="   ">Descrição da Espécie</label>
                 <br/>
                 <input type="text" id="txtDescr" name="txtDescr" value="%s" size="30" maxlength="30" />
                 <br/>
                 
                 <label for="txtOrigem">Continente de Origem</label>
                 <br/>
                 <input type="text" id="txtOrigem" name="txtOrigem" value="%s" size="20" maxlength="20" />
                </p>
                
                <br/>
                <input type="submit" id="btnGravar" name="btnGravar" value="Gravar"/>
                </form> <br> <hr> <br>
                ''' % (pId,pDescr,pOrigem)

        str += self.montaTabela()
        str += self.rodape
        return str

    def montaTabela(self):
        html = '''<table>
                     <tr> 
                        <th> Código </th>
                        <th> Descrição da Espécie </th>
                        <th> Continente de Origem </th>
                        <th> Ações </th>      
                     </tr> '''
        # buscar os dados do banco de dados
        objEspecie = Especie() # criamos um objeto do tipo Especie
        dados = objEspecie.obterEspecies() # será criada uma lista com o resultado o SQL
        for linha in dados:
            html += ''' <tr>
                           <td> %s </td>
                           <td> %s </td>
                           <td> %s </td>
                           <td style="text-align:center;"> 
                              <a href="excluirEspecie?idEsp=%s">[Excluir]</a>
                              <a href="alterarEspecie?idEsp=%s">[Alterar]</a>
                           </td>
                        </tr> ''' % (linha['esp_id'], linha['esp_descricao'],linha['esp_origem'],linha['esp_id'],linha['esp_id'])
        html +=''' </table> <br> <br>'''
        return html

    @cherrypy.expose()
    def gravarEspecie(self,txtId, txtDescr, txtOrigem, btnGravar): # vai ser chamado quando clicar no botão
        if len(txtDescr) > 0:
            # fazer os procedimentos para gravar
            objEspecie = Especie()
            objEspecie.set_descricao(txtDescr)
            objEspecie.set_origem(txtOrigem)
            # se o txtId = 0, representa que estamos inserindo uma nova espécie
            retorno = 0
            if int(txtId) == 0: # nova espécie
                retorno = objEspecie.gravar()
            else: # vai gravar uma alteração no banco de dados
                objEspecie.set_id(int(txtId))
                retorno = objEspecie.alterar()
            if retorno > 0:
                return '''
                        <script>
                           alert(" A espécie %s for gravada com sucesso!!")
                           window.location.href = "/rotaEspecie"
                        </script>
                       ''' % (txtDescr)
            else: # if retorno > 0:  - Quer dizer que deu erro na hora de gravar
                return '''
                        <h2> Erro ao gravar a espécie %s</h2>
                        <a href="/rotaEspecie">voltar</a>
                        ''' % (txtDescr)
        else: # len(txtDescr) > 0:
            return '''
                   <h2> A descrição da espécie deve ser informada</h2>
                   <a href="/rotaEspecie">voltar</a>
               '''

    @cherrypy.expose()
    def excluirEspecie(self,idEsp):
        objEspecie = Especie()
        objEspecie.set_id(int(idEsp))
        if objEspecie.excluir() > 0: # informa se conseguiu excluir ou não
            raise cherrypy.HTTPRedirect('/rotaEspecie') # para atualizar a página após a exclusão (tipo reload)
        else:
            return '''
            <h2>Não foi possível excluir a espécie!!</h2>
            [<a href="/rotaEspecie">Voltar</a>]
            '''

    @cherrypy.expose()
    def alterarEspecie(self,idEsp):
        objEspecie = Especie()
        # buscar no banco a espécie que foi informada no parâmetro
        dadosEspecieSelec = objEspecie.obterEspecie(idEsp)
        # chamar o método para montar o formulário com os dados da espécie selecionada na tabela e carregar nos elementos <input> do formulário
        return self.montaFormulario(dadosEspecieSelec[0]['esp_id'],
                                    dadosEspecieSelec[0]['esp_descricao'],
                                    dadosEspecieSelec[0]['esp_origem'])