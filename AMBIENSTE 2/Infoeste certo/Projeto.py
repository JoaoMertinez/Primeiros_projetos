import cherrypy
import os
#from pageEquipe import PaginaEquipe
from pageEspecie import PaginaEspecie

local_dir = os.path.dirname(__file__)

class Principal():
    topo = open("HTML/telaP.html",encoding="utf8").read()
    #rodape = open("html/rodape.html").read()
    @cherrypy.expose()
    def index(self):
        html = self.topo
        # html = html + '''<br/>
        # <p>Aqui vai o conteúdo central da página inicial do projeto...</p>
        # <p class="cor1">Home do Sistema Pet</p><br/>
        # '''
        html = html

        return html

class Larissa():
    Larissa = open("HTML/portifolio larissa.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Larissa
        html = html
        return html

class Livia():
    Livia = open("HTML/portfolio livia.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Livia
        html = html
        return html

class Lucas():
    Lucas = open("HTML/portfolio lucas.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Lucas
        html = html
        return html

class Maria():
    Maria = open("HTML/portifolio Maria.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Maria
        html = html
        return html

class Maju():
    Maju = open("HTML/portfolio maju.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Maju
        html = html
        return html

class Linux():
    Linux = open("HTML/evento linux.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Linux
        html = html
        return html

class Programacao():
    Programacao = open("HTML/programacao.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Programacao
        html = html
        return html

class Palestra():
    Palestra = open("HTML/palestra.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Palestra
        html = html
        return html

class Fippetec():
    Fippetec = open("HTML/FIPPETEC.html",encoding="utf8")
    @cherrypy.expose
    def index(self):
        html = self.Fippetec
        html = html
        return html

server_config={
'server.socket_host': '127.0.0.1',
'server.socket_port': 81
}
cherrypy.config.update(server_config)

#Para que o cherrypy possa encontrar os arquivos dentro do diretório da aplicação
local_config = {
    "/":{"tools.staticdir.on":True,
         "tools.staticdir.dir":local_dir},
}

#objetos utilizados para rota de navegação
root = Principal() #rota principal
#root.rotaEquipe = PaginaEquipe()
root.rotaEspecie = PaginaEspecie()
root.Larissa = Larissa()
root.Livia = Livia()
root.Lucas = Lucas()
root.Maria = Maria()
root.Maju = Maju()
root.Linux = Linux()
root.Programacao = Programacao()
root.Palestra = Palestra()
root.Fippetec = Fippetec()

cherrypy.quickstart(root,config=local_config)
