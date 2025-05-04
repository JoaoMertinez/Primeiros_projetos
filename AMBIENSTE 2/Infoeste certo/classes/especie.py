from classes.banco import Banco

class Especie(): # está é o nome da classe de Espécies
    '''
        Documentação da classe
        - aqui nó vamos descrever os campos (propriedades) e funções (métodos) para definirmos de acordo com a teoria de Programação Orientada a Objetos
    '''
    # Construtor
    def __init__(self):
        # propriedades privadas
        self.__nome = ''
        self.__email = ''
        self.__cpf = ''
        self.__end_rua = ''
        self.__end_num = 0
        self.__cidade = ''
        self.__genero = ''
        self.__categoria = ''
        self.__foto = ''
        self.__curso1 = 0
        self.__curso2 = 0
        self.__curso3 = 0
        self.__curso4 = 0
        self.__camissa = ''
        self.__banco = Banco() # aqui será criado o objeto que representa o acesso ao Banco de Dados, nós iremos utilizar ela para gravar, excluir, alterar e buscar os dados já gravados no banco
        # propriedades públicas

    # definir os métodos para a nossa classe para colocar os valores nas propriedades
    def set_nome(self, pNome):
        if len(pNome) > 0:
            self.__nome = pNome

    def set_email(self, pEmail):
        if len(pEmail) > 0:
            self.__email = pEmail

    def set_cpf(self, pCpf):
        if len(pCpf) > 0:
            self.__cpf = pCpf

    def set_end_rua(self, pEnd_rua):
        if len(pEnd_rua) > 0:
            self.__end_rua = pEnd_rua

    def set_cidade(self, pCidade):
        if len(pCidade) > 0:
            self.__cidade = pCidade

    def set_genero(self, pGenero):
        if len(pGenero) > 0:
            self.__genero = pGenero

    def set_camissa(self, pCamissa):
        if len(pCamissa) > 0:
            self.__camissa = pCamissa

    def set_end_num(self, pEnd_num):
       # if pEnd_num > 0:
        self.__end_num = pEnd_num
    def set_categoria(self, pCategoria):
        if len(pCategoria) > 0:
            self.__categoria = pCategoria

    # def set_foto(self, pFoto):
    #     self.__foto = pFoto

    def set_curso1(self, pCurso1):
      #  if pCurso1 > 0:
        self.__curso1 = pCurso1

    def set_curso2(self, pCurso2):
    #    if pCurso2 > 0:
        self.__curso2 = pCurso2

    def set_curso3(self, pCurso3):
     #   if pCurso3 > 0:
        self.__curso3 = pCurso3

    def set_curso4(self, pCurso4):
     #   if pCurso4 > 0:
        self.__curso4 = pCurso4

    # def set_origem(self,pOrigem):
    #     self.__origem = pOrigem
    #
    # # métodos para obter os valores das propriedades
    # def get_id(self):
    #     return self.__id
    #
    # def get_descricao(self):
    #     return self.__descricao
    #
    # def get_origem(self):
    #     return self.__origem

    def get_cpf(self):
        return self.__cpf

    def get_nome(self):
        return self.__nome

    def get_email(self):
        return self.__email

    def get_end_rua(self):
        return self.__end_rua

    def get_end_num(self):
        return self.__end_num

    def get_cidade(self):
        return self.__cidade

    def get_genero(self):
        return self.__genero

    def get_categoria(self):
        return self.__categoria

    def get_curso1(self):
        return self.__curso1

    def get_curso2(self):
        return self.__curso2

    def get_curso3(self):
        return self.__curso3

    def get_curso4(self):
        return self.__curso4

    def get_camissa(self):
        return self.__camissa

    # devolver todas as espécies cadastradas no banco de dados na tabela Especies
    def obterEspecies(self):
        sql = '''
              SELECT cad_nome, cad_email, cad_cpf, cad_end_rua, cad_end_num, cad_cidade, cad_genero, cad_categoria, cad_curso1, cad_curso2, cad_curso3, cad_curso4, cad_camissa
              FROM cadastro
              ORDER by cad_nome
              '''
        return self.__banco.executarSelect(sql)

    def gravar(self):  # vai pegar os dados do objeto e gravar na tabela do banco
        sql = ''' INSERT INTO cadastro ( cad_nome, cad_email, cad_cpf, cad_end_rua, cad_end_num, cad_cidade, cad_genero, cad_categoria, cad_curso1, cad_curso2, cad_curso3, cad_curso4, cad_camissa)
                 values ("#nome", "#email", "#cpf", "#end_rua", "#end_num", "#cidade", "#genero", "#categoria", "#curso1", "#curso2", "#curso3", "#curso4", "#camissa")
              '''
        sql = sql.replace('#nome', self.__nome)
        sql = sql.replace('#email', self.__email)
        sql = sql.replace('#cpf', self.__cpf)
        sql = sql.replace('#end_rua', self.__end_rua)
        sql = sql.replace('#end_num', str(self.__end_num))
        sql = sql.replace('#cidade', self.__cidade)
        sql = sql.replace('#genero', self.__genero)
        sql = sql.replace('#categoria', self.__categoria)
       # sql = sql.replace('#foto', self.__foto)
        sql = sql.replace('#curso1', str(self.__curso1))
        sql = sql.replace('#curso2', str(self.__curso2))
        sql = sql.replace('#curso3', str(self.__curso3))
        sql = sql.replace('#curso4', str(self.__curso4))
        sql = sql.replace('#camissa', self.__camissa)

        return self.__banco.executarInsertUpdateDelete(sql)

    # # devolver uma espécia só cdastrada no banco de dados na tabela Especies
    # def obterEspecie(self, pId=0):
    #     if pId != 0:
    #         self.__id = pId
    #     sql = ''' SELECT esp_id, esp_descricao,esp_origem
    #               FROM Especies
    #               where esp_id = #id         '''
    #     sql = sql.replace('#id', str(self.__id))
    #     return self.__banco.executarSelect(sql)

    def obterEspecie(self, pCpf=''):
        if len(pCpf) != 0:
            self.__cpf = pCpf
        sql = ''' SELECT  cad_nome, cad_email, cad_cpf, cad_end_rua, cad_end_num, cad_cidade, cad_genero, cad_categoria, cad_curso1, cad_curso2, cad_curso3, cad_curso4,cad_camissa
                  FROM cadastro
                  where cad_cpf = "#cpf"        '''
        sql = sql.replace("#cpf", str(self.__cpf))
        return self.__banco.executarSelect(sql)


    def excluir(self):
        sql = 'delete from cadastro where cad_cpf = "#cpf"'
        sql = sql.replace("#cpf", str(self.__cpf))
        return self.__banco.executarInsertUpdateDelete(sql)



    # def alterar(self):
    #     sql = 'update Especies set esp_descricao = "#descr", esp_origem = "#origem" where esp_id = #id'
    #     sql = sql.replace('#descr',self.__descricao)
    #     sql = sql.replace('#origem',self.__origem)
    #     sql = sql.replace('#id',str(self.__id))
    #     return self.__banco.executarInsertUpdateDelete(sql)

    def alterar(self):
        sql = 'update cadastro set cad_nome ="#nome", cad_email ="#email", cad_end_rua ="#end_rua", cad_end_num ="#end_num", cad_cidade ="#cidade", cad_genero ="#genero", cad_categoria ="#categoria", cad_curso1 ="#curso1", cad_curso2 ="#curso2", cad_curso3 ="#curso3", cad_curso4 ="#curso4", cad_camissa ="#camissa" where cad_cpf = "#cpf" '

        sql = sql.replace('#nome', self.__nome)
        sql = sql.replace('#email', self.__email)
        sql = sql.replace('#end_rua', self.__end_rua)
        sql = sql.replace('#end_num', str(self.__end_num))
        sql = sql.replace('#cidade', self.__cidade)
        sql = sql.replace('#genero', self.__genero)
        sql = sql.replace('#categoria', self.__categoria)
        # sql = sql.replace('#foto', self.__foto)
        sql = sql.replace('#curso1', str(self.__curso1))
        sql = sql.replace('#curso2', str(self.__curso2))
        sql = sql.replace('#curso3', str(self.__curso3))
        sql = sql.replace('#curso4', str(self.__curso4))
        sql = sql.replace('#camissa', self.__camissa)
        sql = sql.replace('#cpf', self.__cpf)
        return self.__banco.executarInsertUpdateDelete(sql)