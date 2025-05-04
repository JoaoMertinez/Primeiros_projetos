def adicionar_aluno():
    nome_aluno = input("Digite o nome do aluno: ")
    notas_aluno = []
    while True:
        try:
            nota = float(input("Digite a nota do aluno (ou < que 0 para parar): "))
            if 0 <= nota <= 10:
                notas_aluno.append(nota)
            elif nota < 0:
                break
            else:
                print("Nota incorreta!\nPor favor, insira uma nota entre 0 e 10!")
        except ValueError:
            print("Por favor, insira um número válido para a nota do aluno.")
    aluno = {'nome': nome_aluno, 'notas': notas_aluno}
    return aluno

def atualizar_notas_aluno(alunos, nome_aluno):
    for aluno in alunos:
        if aluno['nome'] == nome_aluno:
            notas_aluno = []
            while True:
                try:
                    nota = float(input("Digite a nova nota do aluno (ou < que 0 para parar): "))
                    if 0 <= nota <= 10:
                        notas_aluno.append(nota)
                    elif nota < 0:
                        break
                    else:
                        print("Nota incorreta!\nPor favor, insira uma nota entre 0 e 10!")
                except ValueError:
                    print("Por favor, insira um número válido para a nota do aluno.")
            aluno['notas'] = notas_aluno
            print("**Notas atualizadas**")
            return
    print("Aluno não encontrado")

def calcular_media_aluno(aluno):
    notas = aluno['notas']
    if notas:
        return sum(notas) / len(notas)
    else:
        return 0

def listar_alunos(alunos):
    for aluno in alunos:
        print("Nome: {aluno['nome']}, Notas: {aluno['notas']}, Média: {calcular_media_aluno(aluno)}")

def encontrar_maior_media(alunos):
    if not alunos:
        print("Nenhum aluno cadastrado.")
        return
    aluno_maior_media = max(alunos, key=calcular_media_aluno)
    print(f"Aluno com a maior média: {aluno_maior_media['nome']} - Média: {calcular_media_aluno(aluno_maior_media)}")

def encontrar_menor_media(alunos):
    if not alunos:
        print("Nenhum aluno cadastrado.")
        return
    aluno_menor_media = min(alunos, key=calcular_media_aluno)
    print(f"Aluno com a menor média: {aluno_menor_media['nome']} - Média: {calcular_media_aluno(aluno_menor_media)}")

def menu():
    lista_alunos = []

    print("\n")
    print("\n*** Sistema Escolar ***")
    print("[1] Cadastrar aluno")
    print("[2] Atualizar notas")
    print("[3] Calcular média")
    print("[4] Listar alunos")
    print("[5] Encontrar aluno com a maior média")
    print("[6] Encontrar aluno com a menor média")
    print("[0] Encerrar\n")
    resp = input("\nEscolha uma opção: ")

    while resp > "0":
        print("\n")
        if resp == "1":
            aluno = adicionar_aluno()
            lista_alunos.append(aluno)
        elif resp == "2":
            nome_aluno = input("Digite o nome do aluno para atualizar as notas: ")
            atualizar_notas_aluno(lista_alunos, nome_aluno)
        elif resp == "3":
            nome_aluno = input("Digite o nome do aluno para calcular a média: ")
            for aluno in lista_alunos:
                if aluno['nome'] == nome_aluno:
                    print(f"Média do aluno {nome_aluno}: {calcular_media_aluno(aluno)}")
                    break
            else:
                print("Aluno não encontrado.")
        elif resp == "4":
            listar_alunos(lista_alunos)
        elif resp == "5":
            encontrar_maior_media(lista_alunos)
        elif resp == "6":
            encontrar_menor_media(lista_alunos)
        elif resp == "0":
            print("Programa encerrado. Adeus!")
            break
        else:
            print("Opção inválida. Por favor, escolha novamente.")

        print("\n")
        print("\n*** Sistema Escolar ***")
        print("[1] Cadastrar aluno")
        print("[2] Atualizar notas")
        print("[3] Calcular média")
        print("[4] Listar alunos")
        print("[5] Encontrar aluno com a maior média")
        print("[6] Encontrar aluno com a menor média")
        print("[0] Encerrar\n")
        resp = input("\nEscolha uma opção: ")

    if resp == "0":
        print("\nPrograma encerrado. Até a próxima!")
menu()
